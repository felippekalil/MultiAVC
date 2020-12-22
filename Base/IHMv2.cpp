#include "IHMv2.h"
#include "Icones.h"

namespace IHMv2
{
	Ihm* Ihm::pntrEstatico;

	void Ihm::setFreqBuzzer(const uint8_t nFreq)
	{
		switch (nFreq)
		{
		default:
			TCCR2B = (0 << FOC0A) | (0 << FOC0B) | (0 << WGM02) | 
				(0 << CS02) | (1 << CS01) | (1 << CS00);
			break;
		case 1:
			TCCR2B = (0 << FOC0A) | (0 << FOC0B) | (0 << WGM02) |
				(0 << CS02) | (1 << CS01) | (0 << CS00);
			break;
		case 2:
			TCCR2B = (0 << FOC0A) | (0 << FOC0B) | (0 << WGM02) | 
				(1 << CS02) | (0 << CS01) | (1 << CS00);
			break;
		}
	}

	void Ihm::apitarBuzzerInc()
	{
		modoBuzzer = 0;
		apitaBuzzer = tempoBuzzerInc;
	}

	void Ihm::apitarBuzzerEnter()
	{
		modoBuzzer = 1;
		apitaBuzzer = tempoBuzzerInc * 8;
	}

	void Ihm::apitarBuzzerVoltar()
	{
		modoBuzzer = 2;
		apitaBuzzer = tempoBuzzerInc * 6;
	}

	void Ihm::apitarBuzzer(const uint8_t tipo)
	{
		switch (tipo)
		{
		default:
			break;
		case 1:
			apitarBuzzerInc();
			break;
		case 2:
			apitarBuzzerEnter();
			break;
		case 3:
			apitarBuzzerVoltar();
			break;
		}
	}

	void Ihm::processaBuzzer()
	{
		if (apitaBuzzer)
		{
			switch (modoBuzzer)
			{
			default:
				setFreqBuzzer(0);
				break;
			case 1:
				if (apitaBuzzer == tempoBuzzerInc * 8)
					setFreqBuzzer(0);
				if (apitaBuzzer == tempoBuzzerInc * 6)
					setFreqBuzzer(1);
				break;
			case 2:
				if (apitaBuzzer == tempoBuzzerInc * 6)
					setFreqBuzzer(0);
				if (apitaBuzzer == tempoBuzzerInc * 3)
					setFreqBuzzer(2);
				break;
			}
			analogWrite(buzzer, 10);
			apitaBuzzer--;
		}
		else
			digitalWrite(buzzer, false);
	}

	void Ihm::handleEncoder()
	{
		if (aguardaMenu || clickVoltar > 0)
			return;
		apitarBuzzerInc();
		if (digitalRead(encoderPinB) == digitalRead(encoderPinA)) //dec
			menuAtual->onEncdrDec();
		else //inc
			menuAtual->onEncdrInc();
	}

	void Ihm::handleSwitch()
	{
		if (aguardaMenu)
			return;
		if (digitalRead(SWITCH))
			clickVoltar = tempoVoltar;
		else
		{
			aguardaMenu = tempoAguardaMenu / 2;
			if (clickVoltar) // se ainda está contando
			{
				clickVoltar = 0;
				apitarBuzzerEnter(); 
				possivelAjusteVar = true;
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
		tempoBuzzerInc = duracaoBuzzer / tLoop;
		if (!tempoBuzzerInc)
			tempoBuzzerInc = 1;
		tempoVoltar = duracaoVoltar / tLoop;
		if (!tempoVoltar)
			tempoVoltar = 1;
		tempoAguardaMenu = duracaoAguardaMenu / tLoop;
		if (!tempoAguardaMenu)
			tempoAguardaMenu = 1;
	}

	Ihm::Ihm(MenuBase* menu, const uint16_t tLoop): lcd(rs, en, d4, d5, d6, d7)
	{
		tempoBuzzerInc = duracaoBuzzer / tLoop;
		if (!tempoBuzzerInc) 
			tempoBuzzerInc = 1;
		tempoVoltar = duracaoVoltar / tLoop;
		if (!tempoVoltar)
			tempoVoltar = 1;
		tempoAguardaMenu = duracaoAguardaMenu / tLoop;
		if (!tempoAguardaMenu)
			tempoAguardaMenu = 1;
		atualizaMenu(menu);
	}

	void Ihm::atualizaMenu(MenuBase* menu)
	{
		menuAtual = menu;
		nCharLogo = 0;
		aguardaMenu = tempoAguardaMenu;
		menuAtual->onMenuIni([](const MenuBase::Logo logo) { pntrEstatico->createLogo(logo); });
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

	void Ihm::createLogo(const MenuBase::Logo logo)
	{
		uint8_t i;
		for (i = 0; i < 8; i++)
		{
			if (*(logo.logoPtr + i * 8) >= B100000 || logo.logoPtr == nullptr)
				break;
			createChar(i, logo.logoPtr + i * 8);
		}
		nCharLogo = i;

		if(logo.charExtra != nullptr)
		{
			createChar(logo.posCharExtra, logo.charExtra);
			if (logo.posCharExtra > i)
				nCharLogo = logo.posCharExtra;
		}

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
			delay(150);
		}
	}

	void Ihm::setup()
	{
		pinMode(LED_BUILTIN, OUTPUT);
		pinMode(buzzer, OUTPUT);
		pinMode(encoderPinA, INPUT);
		pinMode(encoderPinB, INPUT);
		pinMode(SWITCH, INPUT);

		pntrEstatico = this;
		attachInterrupt(0, []() { pntrEstatico->handleEncoder(); }, CHANGE);
		attachInterrupt(1, []() { pntrEstatico->handleSwitch(); }, CHANGE);

		lcd.begin(16, 2);
		MenuBase::Logo logoIni = { reinterpret_cast<uint8_t*>(&Icones::logoLabsolda), 1 };
		createLogo(logoIni);

		//telaInicialLabsolda();

		logoIni = { reinterpret_cast<uint8_t*>(&Icones::logoRobo), 11 };
		createLogo(logoIni);

		lcd.clear();
		imprimeLogo();

		lcd.setCursor(2, 0);
		lcd.print("MultiAVC");
		lcd.setCursor(2, 1);
		lcd.print("  v1.0");
		delay(1500);
	}

	void Ihm::loop()
	{
		processaBuzzer();
		if (clickVoltar)
		{
			if (clickVoltar == 1)
			{
				apitarBuzzerVoltar();
				aguardaMenu = tempoAguardaMenu;
				possivelAjusteVar = true;
				menuAtual->onVoltar();
			}
			clickVoltar--;
		}
		if (aguardaMenu)
			aguardaMenu--;
		if (menuAtual->apitar)
		{
			apitarBuzzer(menuAtual->apitar);
			menuAtual->apitar = 0;
		}
		menuAtual->onLoop();
		imprimeInterface();
	}

	bool Ihm::varAjustadas()
	{
		const auto ajst = possivelAjusteVar;
		possivelAjusteVar = false;
		return ajst;
	}
}
