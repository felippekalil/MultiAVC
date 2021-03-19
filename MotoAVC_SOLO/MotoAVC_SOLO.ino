/*
 Name:		MotoAVC_SOLO.ino
 Created:	11/26/2020 8:55:52 PM
 Author:	Kalil
*/

constexpr auto TLOOP = 50; // ms;
constexpr auto TPLOT = 100; // ms;
constexpr auto saidaLoop = 12;

#include <LiquidCrystal.h>
#include "IHMv2.h"
#include "src/Menus.h"
#include "src/ControleAVC.h"
#include "src/SalvarDados.h"

using namespace IHMv2;

namespace IOs
{
	constexpr int IN_1 = 7;
	constexpr int IN_2 = 8;
	constexpr int OUT_1 = 9;
	constexpr int OUT_2 = 10;

	void inicializaIOs()
	{
		pinMode(IN_1, INPUT);
		pinMode(IN_2, INPUT);
		pinMode(OUT_1, OUTPUT);
		pinMode(OUT_2, OUTPUT);
	}

	void atualizaIOs()
	{
		digitalWrite(OUT_1, !digitalRead(IN_1));
		digitalWrite(OUT_2, !digitalRead(IN_2));
	}
}


Ihm ihm(TLOOP);

void plot()
{
	Serial.print(Controle.referencia);
	Serial.print(" ");
	Serial.println(Controle.valorTensaoDoArco);//*/
	digitalWrite(saidaLoop, !digitalRead(saidaLoop));
}

void setup() {
	Serial.begin(9600);
	//Serial.println(F("Inicializado!"));
	IOs::inicializaIOs();
	pinMode(saidaLoop, OUTPUT);
	Controle.setupControle();
	Menus.init(TLOOP);
	ihm.setup();
	ihm.atualizaMenu(Menus.menus[Menus.menuIhmIndex]);
	Eeprom::inicializaVarsEeprom();
	Eeprom::carregaEeprom();
}

void loop() {
	Controle.atua();
	const auto tAtual = millis();
	if (tAtual % TLOOP == 0)
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
	IOs::atualizaIOs();
	if (tAtual % TPLOT == 0)
		plot();//*/
}
