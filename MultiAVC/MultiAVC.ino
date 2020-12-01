/*
 Name:		MultiAVC.ino
 Created:	9/11/2020 3:09:05 PM
 Author:	Felippe Kalil Mendonça
*/
#include <LiquidCrystal.h>
#include "MenusIni.h"
#include "IHMv2.h"

using namespace IHMv2;
constexpr uint16_t tLoop = 50; // lembrar de ajustar no MenusIni.h

Ihm ihm(tLoop);

void setup() {
    Serial.begin(9600);
    Serial.println("Inicializado!");
    Menus::tLoop = tLoop;
    ihm.setup();    
    ihm.atualizaMenu(Menus::menus[Menus::menuIhmIndex]);
}

void loop() {
    if (millis() % tLoop == 0)
    {
        if(Menus::menuIhmIndex != Menus::menuIndexAnterior)
            ihm.atualizaMenu(Menus::menus[Menus::menuIhmIndex]);
        Menus::menuIndexAnterior = Menus::menuIhmIndex;
        ihm.loop();
    }
}
