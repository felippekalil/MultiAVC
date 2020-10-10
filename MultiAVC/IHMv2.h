#pragma once

#include <LiquidCrystal.h>
#include "Menu.h"
#ifndef _IHMV2_H
	#define _IHMV2_H

namespace IHMv2
{

	inline void pause()
	{
		while (true) {}
	}

	class Ihm
	{
		const int encoderPinA = 2;
		const int encoderPinB = 4;
		const int buzzer = 5;
		uint16_t tempoBuzzer;
		const int SWITCH = 3;
		uint16_t tempoVoltar;
		const uint16_t duracaoBuzzer = 200;
		const uint16_t duracaoVoltar = 600;
		byte(*logoIni)[8];

		const int rs = A4, en = A5, d4 = A0, d5 = A1, d6 = A2, d7 = A3;
		LiquidCrystal lcd;
		static Ihm* instancia;
		volatile uint16_t apitaBuzzer = 0, clickVoltar = 0;
		uint8_t nCharLogo = 0, offsetLogo = 0;

		void apitarBuzzer();

		void handleEncoder();

		void handleSwitch();

		void imprimeInterface();

		Menu* menuAtual{};

	public:
		explicit Ihm(uint16_t tLoop);

		explicit Ihm(Menu* menu, uint16_t tLoop);

		void atualizaMenu(Menu* menu);

		bool varAjustadas() const;

		void imprimeLogo();

		void createChar(uint8_t index, uint8_t customChar[]);

		void createLogo(Menu::Logo logo);

		void telaInicialLabsolda();

		void setup();

		void loop();
	};
}
#endif