#include "IHMv2.H"
#include "Icones.h"

namespace IHMv2
{
	Ihm* Ihm::instancia;

	void Ihm::apitarBuzzer()
	{
		apitaBuzzer = tempoBuzzer;
	}

	void Ihm::handleEncoder()
	{
		apitarBuzzer();
		if (digitalRead(encoderPinB) == digitalRead(encoderPinA)) //dec
			menuAtual->onEncdrDec();
		else //inc
			menuAtual->onEncdrInc();
	}

	void Ihm::handleSwitch()
	{
		if (digitalRead(SWITCH))
			clickVoltar = tempoVoltar;
		else
		{
			apitarBuzzer();
			if (clickVoltar) // se ainda está contando
			{
				clickVoltar = 0;
				menuAtual->onClick();
			}
		}
	}

	void Ihm::imprimeInterface()
	{
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(menuAtual->linhaSuperior);
		lcd.setCursor(0, 1);
		lcd.print(menuAtual->linhaInferior);
		imprimeLogo();
	}

	Ihm::Ihm(const uint16_t tLoop): lcd(rs, en, d4, d5, d6, d7)
	{
		tempoBuzzer = duracaoBuzzer / tLoop;
		tempoVoltar = duracaoVoltar / tLoop;
		this->logoIni = logoIni;
	}

	Ihm::Ihm(Menu* menu, const uint16_t tLoop): lcd(rs, en, d4, d5, d6, d7)
	{
		tempoBuzzer = duracaoBuzzer / tLoop;
		tempoVoltar = duracaoVoltar / tLoop;
		atualizaMenu(menu);
		this->logoIni = logoIni;
	}

	void Ihm::atualizaMenu(Menu* menu)
	{
		menuAtual = menu;
		nCharLogo = 0;
		menuAtual->onMenuIni([](const Menu::Logo logo) { instancia->createLogo(logo); });
	}

	void Ihm::imprimeLogo()
	{
		lcd.setCursor(offsetLogo, 0);
		for (uint8_t i = 0; i < nCharLogo; i++)
		{
			if (i == nCharLogo / 2)
				lcd.setCursor(offsetLogo, 1);
			lcd.write(static_cast<uint8_t>(i));
		}
	}

	void Ihm::createChar(const uint8_t index, uint8_t customChar[])
	{
		lcd.createChar(index, customChar);
	}

	void Ihm::createLogo(const Menu::Logo logo)
	{
		uint8_t i;
		for (i = 0; i < 8; i++)
		{
			if (logo.logo[i][0] >= B100000)
				break;
			createChar(i, logo.logo[i]);
		}
		nCharLogo = i;
		this->offsetLogo = logo.offset;
	}

	void Ihm::telaInicialLabsolda()
	{
		imprimeLogo();
		lcd.setCursor(5, 0);
		lcd.print(" LABSOLDA");
		const String inst = "Instituto de Soldagem e Mecatronica";
		const auto iniLcd = 5;
		const auto lenght = 15 - iniLcd;
		const auto lastLcd = inst.length() - lenght;
		delay(1000);
		for (auto i = 0; i < lastLcd; i++)
		{
			lcd.setCursor(iniLcd, 1);
			lcd.print(inst.substring(i, i + lenght + 1));
			delay(200);
		}
	}

	void Ihm::setup()
	{
		pinMode(LED_BUILTIN, OUTPUT);
		pinMode(buzzer, OUTPUT);
		pinMode(encoderPinA, INPUT);
		pinMode(encoderPinB, INPUT);
		pinMode(SWITCH, INPUT);

		instancia = this;
		attachInterrupt(0, []() { instancia->handleEncoder(); }, CHANGE);
		attachInterrupt(1, []() { instancia->handleSwitch(); }, CHANGE);

		lcd.begin(16, 2);
		const Menu::Logo logoLab = { Icones::logoLabsolda, 1 };
		createLogo(logoLab);

		//telaInicialLabsolda();

		lcd.clear();
		imprimeLogo();

		lcd.setCursor(5, 0);
		lcd.print(" MultiAVC");
		lcd.setCursor(5, 1);
		lcd.print("   v1.0");
		delay(1500);
	}

	void Ihm::loop()
	{
		if (apitaBuzzer)
		{
			apitaBuzzer--;
			digitalWrite(buzzer, true);
		}
		else
			digitalWrite(buzzer, false);
		if (clickVoltar)
		{
			if (clickVoltar == 1)
			{
				apitarBuzzer();
				menuAtual->onVoltar();
			}
			clickVoltar--;
		}
		menuAtual->onLoop();
		imprimeInterface();
	}
}
