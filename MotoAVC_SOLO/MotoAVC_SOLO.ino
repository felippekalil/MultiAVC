/*
 Name:		MotoAVC_SOLO.ino
 Created:	11/26/2020 8:55:52 PM
 Author:	Kalil
*/

#define TLOOP 50

#include <LiquidCrystal.h>
#include "IHMv2.h"
#include "src/Menus.h"

using namespace IHMv2;

Ihm ihm(TLOOP);

void setup() {
    Serial.begin(9600);
    Serial.println("Inicializado!");
    Menus.init(TLOOP);
    ihm.setup();
    ihm.atualizaMenu(Menus.menus[Menus.menuIhmIndex]);
}

void loop() {
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
}
