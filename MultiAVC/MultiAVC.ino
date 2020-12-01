/*
 Name:		MultiAVC.ino
 Created:	9/11/2020 3:09:05 PM
 Author:	Felippe Kalil Mendonça
*/
#define TLOOP 50

#include <LiquidCrystal.h>
#include "MenusIni.h"
#include "IHMv2.h"

using namespace IHMv2;

Ihm ihm(TLOOP);

void setup() {
    Serial.begin(9600);
    Serial.println("Inicializado!");
    Menus::tLoop = TLOOP;
    ihm.setup();    
    ihm.atualizaMenu(Menus::menus[Menus::menuIhmIndex]);
}

void loop() {
    if (millis() % TLOOP == 0)
    {
        if(Menus::menuIhmIndex != Menus::menuIndexAnterior)
            ihm.atualizaMenu(Menus::menus[Menus::menuIhmIndex]);
        Menus::menuIndexAnterior = Menus::menuIhmIndex;
        ihm.loop();
    }
}
