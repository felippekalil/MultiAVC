/*
 Name:		MotoAVC_SOLO.ino
 Created:	11/26/2020 8:55:52 PM
 Author:	Kalil
*/

constexpr auto T_LOOP = 50; // ms;
constexpr auto T_PLOT = 100; // ms;
constexpr auto T_LCD_RESET = 4000; // ms;
constexpr auto saidaLoop = 12;

//#define PRINT_SERIAL

#include <LiquidCrystal.h>
#include "IHMv2.h"
#include "src/Menus.h"	
#include "src/ControleAVC.h"
#include "src/SalvarDados.h"

using namespace IHMv2;

namespace IOs
{
	constexpr uint8_t IN_1 = 7;
	constexpr uint8_t IN_2 = 8;
	constexpr uint8_t OUT_1 = 9;
	constexpr uint8_t OUT_2 = 10;

	void inicializaIOs()
	{
		pinMode(IN_1, INPUT);
		pinMode(IN_2, INPUT);
		pinMode(OUT_1, OUTPUT);
		pinMode(OUT_2, OUTPUT);
	}

	void atualizaIOs() // para testes
	{
		digitalWrite(OUT_1, !digitalRead(IN_1));
		digitalWrite(OUT_2, !digitalRead(IN_2));
	}
}


Ihm ihm(T_LOOP);

void plot()
{
	Serial.print(Controle.referencia);
	Serial.print(" ");
	Serial.println(Controle.valorTensaoDoArco);//*/
	digitalWrite(saidaLoop, !digitalRead(saidaLoop));
}

void setup() {
	Serial.begin(9600);
	IOs::inicializaIOs();
	Eeprom::inicializaVarsEeprom();
	Eeprom::carregaEeprom();
	pinMode(saidaLoop, OUTPUT);
	Controle.setupControle(IOs::OUT_1, IOs::OUT_2);
	Menus.init(T_LOOP);
	ihm.setup();
	ihm.atualizaMenu(Menus.menus[Menus.menuIhmIndex]);
}

void loop() {
	Controle.atua();
	const auto tAtual = millis();
	if (tAtual % T_LOOP == 0)
	{
		if (Menus.menuIhmIndex != Menus.menuIndexAnterior)
		{
			Menus.menus[Menus.menuIhmIndex]->menuAnterior = Menus.menuIndexAnterior;
			ihm.atualizaMenu(Menus.menus[Menus.menuIhmIndex]);
		}
		if (Menus.menuIhmIndex != Nada)
			Menus.menuIndexAnterior = Menus.menuIhmIndex;
		ihm.loop();
	}
	if (ihm.varAjustadas())
		Eeprom::atualizaEeprom();//*/
	//IOs::atualizaIOs();
	if (tAtual % T_LCD_RESET == 0)
		ihm.iniLcd();//*/
#ifndef PRINT_SERIAL
	if (tAtual % T_PLOT == 0)
		plot();//*/
#endif
}

#ifdef PRINT_SERIAL
void serialEvent() {
	while (Serial.available()) 
		ihm.interfaceSerial(static_cast<char>(Serial.read()));
}
#endif