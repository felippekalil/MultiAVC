#pragma once

#include <LiquidCrystal.h>
#include "MenuBase.h"
#ifndef _IHMV2_H
#define _IHMV2_H

namespace IHMv2
{
	inline void pause() { while (true) {} }
	const char inst[] PROGMEM = "Instituto de Soldagem e Mecatronica";

	class Ihm
	{
		const int encoderPinA = 2;
		const int encoderPinB = 4;
		const int buzzer = 11;
		uint16_t tempoBuzzerInc;
		const int SWITCH = 3;
		uint16_t tempoVoltar;
		uint16_t tempoAguardaMenu;
		const uint16_t duracaoBuzzer = 50;
		const uint16_t duracaoVoltar = 600;
		const uint16_t duracaoAguardaMenu = 600;

		const int rs = A5, en = A4, d4 = A3, d5 = A2, d6 = A1, d7 = A0;
		LiquidCrystal lcd;
		static Ihm* pntrEstatico;
		volatile uint16_t aguardaMenu = 0, apitaBuzzer = 0, clickVoltar = 0;
		volatile uint8_t modoBuzzer = 0;
		uint8_t nCharLogo = 0, offsetLogo = 0;
		bool possivelAjusteVar = false;
		bool lockControles = false;
		int velEncoder = 0;

		static void setFreqBuzzer(uint8_t nFreq);

		void apitarBuzzerInc();

		void apitarBuzzerDec();

		void apitarBuzzerEnter();

		void apitarBuzzerVoltar();

		void apitarBuzzer(uint8_t tipo);

		void processaBuzzer();

		void handleEncoder();

		void handleSwitch();

		void imprimeInterface();

		MenuBase* menuAtual{};

	public:
		explicit Ihm(uint16_t tLoop);
		explicit Ihm(MenuBase* menu, uint16_t tLoop);

		void atualizaMenu(MenuBase* menu);

		void imprimeLogo();

		void createChar(uint8_t index, uint8_t customChar[]);

		void createLogo(const Logo& logo);

		void telaInicialLabsolda();

		void iniLcd();

		void setup();

		void loop();

		bool varAjustadas();

		void bloqueiaControles();

		void liberaControles();

		void interfaceSerial(char c) const;
	};
}
#endif