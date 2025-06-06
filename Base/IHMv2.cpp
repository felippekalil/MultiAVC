#include "IHMv2.h"
#include "Icones.h"

//#define PRINT_SERIAL
//#define MEMORIA

int availableMemory() {
	auto size = 1024; // Use 2048 with ATmega328
	byte* buf;

	while ((buf = static_cast<byte*>(malloc(--size))) == nullptr)
		;

	free(buf);

	return size;
}

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

	void Ihm::apitarBuzzerDec()
	{
		modoBuzzer = 3;
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
		//return;
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
			case 3:
				setFreqBuzzer(2);
				break;
			}
			analogWrite(buzzer, 200);
			apitaBuzzer--;
		}
		else
			digitalWrite(buzzer, false);
	};

	void Ihm::handleEncoder()
	{
		if (aguardaMenu || clickVoltar > 0 || lockControles)
			return;
		auto mult = velEncoder;
		if (mult < 1)
			mult = 1;
		if (digitalRead(encoderPinB) == digitalRead(encoderPinA)) //dec
		{
			apitarBuzzerDec();
			menuAtual->onEncdrDec(mult);
		}
		else //inc
		{
			apitarBuzzerInc();
			menuAtual->onEncdrInc(mult);
		}
		if (velEncoder < 10)
			velEncoder++;
	}

	void Ihm::handleSwitch()
	{
		if (aguardaMenu || lockControles)
			return;
		if (digitalRead(SWITCH))
			clickVoltar = tempoVoltar;
		else
		{
			aguardaMenu = tempoAguardaMenu / 2;
			if (clickVoltar) // se ainda est� contando
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
#ifdef PRINT_SERIAL
		Serial.println(menuAtual->linhaSuperior);
		Serial.println(menuAtual->linhaInferior);
#endif
		imprimeLogo();
#ifdef MEMORIA
		Serial.print("Free:");
		Serial.println(availableMemory());
#endif
	}

	Ihm::Ihm(const uint16_t tLoop) : lcd(rs, en, d4, d5, d6, d7)
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

	Ihm::Ihm(MenuBase* menu, const uint16_t tLoop) : lcd(rs, en, d4, d5, d6, d7)
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
		menuAtual->onMenuIni([](const Logo& logo) { pntrEstatico->createLogo(logo); });
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

	void Ihm::createLogo(const Logo& logo)
	{
		uint8_t temp[64];
		memcpy_P(temp, logo.logoPtr, 64);
		const uint8_t* logoPtr = reinterpret_cast<uint8_t*>(&temp);

		uint8_t i;
		for (i = 0; i < 8; i++)
		{
			if (*(logoPtr + i * 8) >= B100000 || logoPtr == nullptr)
				break;
			createChar(i, const_cast<uint8_t*>(logoPtr + i * 8));
		}
		nCharLogo = i;

		memcpy_P(temp, logo.charExtra, 8);

		if (logo.charExtra != nullptr)
		{
			createChar(logo.posCharExtra, const_cast<uint8_t*>(logoPtr));
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
		const auto iniLcd = 5;
		const auto lenght = 15 - iniLcd;
		const auto lastLcd = strlen_P(inst) - lenght;
		char texto[36];
		memcpy_P(&texto, &inst, 36);

		for (auto i = 0; i < lastLcd; i++)
		{
			lcd.setCursor(iniLcd, 1);
			lcd.print(texto + i);
			delay(150);
		}
	}

	void Ihm::iniLcd()
	{
		lcd.begin(16, 2);
		if (menuAtual != nullptr)
			menuAtual->atualizaLogo();
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

		iniLcd();

		bloqueiaControles();

		Logo logoIni = { reinterpret_cast<const uint8_t*>(&Icones::LOGO_LABSOLDA), 1 };
		createLogo(logoIni);

		telaInicialLabsolda();//*/

		logoIni = { reinterpret_cast<const uint8_t*>(&Icones::LOGO_ROBO), 11 };
		createLogo(logoIni);

		lcd.clear();
		imprimeLogo();

		lcd.setCursor(2, 0);
		lcd.print("MotoAVC");
		lcd.setCursor(2, 1);
		lcd.print("  v1.0");
		delay(1500);//*/
		liberaControles();
		apitarBuzzerEnter();
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
		if (velEncoder > 0)
			velEncoder--;
	}

	bool Ihm::varAjustadas()
	{
		const auto ajst = possivelAjusteVar;
		possivelAjusteVar = false;
		return ajst;
	}

	void Ihm::bloqueiaControles() { lockControles = true; }

	void Ihm::liberaControles() { lockControles = false; }

	void Ihm::interfaceSerial(const char c) const
	{
		switch (c)
		{
		case 'D':
		case 'd':
			menuAtual->onEncdrDec(1);
			break;
		case 'I':
		case 'i':
			menuAtual->onEncdrInc(1);
			break;
		case 'E':
		case 'e':
			menuAtual->onClick();
			break;
		case 'V':
		case 'v':
			menuAtual->onVoltar();
			break;
		default: 
			break;;
		}
	}
}
