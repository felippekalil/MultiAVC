/*
 Name:		MotoAVC_SOLO.ino
 Created:	11/26/2020 8:55:52 PM
 Author:	Kalil
*/

constexpr auto TLOOP = 50; // ms;
constexpr auto saidaLoop = 12;

#include <LiquidCrystal.h>
#include "IHMv2.h"
#include "src/Menus.h"
#include "src/ControleAVC.h"
#include "src/SalvarDados.h"

using namespace IHMv2;

Ihm ihm(TLOOP);

void setup() {
    Serial.begin(115200);
    Serial.println(F("Inicializado!"));
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
    if (millis() % TLOOP == 0)
    {
        if (Menus.menuIhmIndex != Menus.menuIndexAnterior)
        {
            //Serial.println("MenuAnt = " + String(menuIndexAnterior));
            //Serial.println("MenuAtual = " + String(menuIhmIndex));
            Menus.menus[Menus.menuIhmIndex]->menuAnterior = Menus.menuIndexAnterior;
            ihm.atualizaMenu(Menus.menus[Menus.menuIhmIndex]);
        }
        if(Menus.menuIhmIndex != Nada)
            Menus.menuIndexAnterior = Menus.menuIhmIndex;
        ihm.loop();
    }
    if(ihm.varAjustadas())
	    Eeprom::atualizaEeprom();
    //digitalWrite(saidaLoop, !digitalRead(saidaLoop));
}
