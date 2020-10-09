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

namespace Menus
{
    MenusEnum::Menus menuIhm = MenusEnum::Menus::Principal;
    MenusEnum::Menus menuAnterior = MenusEnum::Menus::Principal;

    String nomeModos[] = { "MOTOMAN","CNC", "Step&Dir" };
    uint8_t logoSize = 3, offsetLogo = 15 - logoSize - 1;
    Menu::Logo logos1[] = { {logoRobo, offsetLogo}, {logoCnc, offsetLogo - 1}, {logoStepDir, offsetLogo}, {logoLabsolda, offsetLogo} };
    uint8_t offset = -(logoSize + 1);
    MenuBase menuInicial("Modo", &menuIhm, MenusEnum::Principal, 3, nomeModos, logos1, logoSize, offset);

    String nomeEnums[] = { "TIG","TIG HF", " MIG Conv.", " MIG Puls." };
    byte(*logos2[])[8] = { logoTig, logoTigHf, logoMigConv, logoMigPulse };
    uint8_t logoSize2 = 3, offset2 = logoSize2 + 1, offsetLogo2 = 2;
    MenuBase menuProcessos("Processo", &menuIhm, MenusEnum::Principal, 4, nomeEnums, logos2, logoSize2, offset2, offsetLogo2);

    Menu* menus[2] = { &menuInicial , &menuProcessos };//*/	
}

void setup() {
    Serial.begin(9600);
    Serial.println("Inicializado!");
   // inicializaMenuInicial();
    ihm.setup();//*/    
   // MenuProcessos::inicializaMenuInicial(&menuIhm);
    ihm.atualizaMenu(Menus::menus[Menus::menuIhm]);//*/
}

void loop() {
    if (millis() % tLoop == 0)
    {
        if(Menus::menuIhm != Menus::menuAnterior)
            ihm.atualizaMenu(Menus::menus[Menus::menuIhm]);
        Menus::menuAnterior = Menus::menuIhm;
        ihm.loop();
    }
}
