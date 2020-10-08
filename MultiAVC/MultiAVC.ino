/*
 Name:		MultiAVC.ino
 Created:	9/11/2020 3:09:05 PM
 Author:	Felippe Kalil Mendonça
*/
#include <LiquidCrystal.h>
#include "MenusIni.h"
#include "Menu.h"
#include "IHMv2.h"
using namespace IHMv2;

Ihm ihm(tLoop);
MenusEnum::Menus menuIhm = MenusEnum::Menus::Principal;
MenusEnum::Menus menuAnterior = MenusEnum::Menus::Principal;
Menu* menus[2] = { &MenuPrincipal::menuPrincipal , &MenuProcessos::menuProcessos };

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    Serial.println("Inicializado!");
   // inicializaMenuInicial();
    ihm.setup();//*/    
    MenuPrincipal::inicializaMenuInicial(&menuIhm);
    MenuProcessos::inicializaMenuInicial(&menuIhm);
    //ihm.atualizaMenu(&MenuProcessos::menuProcessos);/*
    ihm.atualizaMenu(menus[menuIhm]);//*/
}

// the loop function runs over and over again until power down or reset
void loop() {
    if (millis() % tLoop == 0)
    {
        if(menuIhm != menuAnterior)
            ihm.atualizaMenu(menus[menuIhm]);
        menuAnterior = menuIhm;
        ihm.loop();
    }
}
