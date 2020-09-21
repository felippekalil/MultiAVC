/*
 Name:		MultiAVC.ino
 Created:	9/11/2020 3:09:05 PM
 Author:	Felippe Kalil Mendonça
*/
#include <LiquidCrystal.h>
#include "MenusIni.h"
#include "Menu.h"
#include "IHMv2.h"
#include "MenusIni.h"
using namespace IHMv2;

Ihm ihm(tLoop);

void trocaMenuPrincipal(MenusEnum::Menus menu)
{
	switch (menu)
	{
    default:
        ihm.atualizaMenu(&MenuPrincipal::menuPrincipal);
        break;
    case MenusEnum::Menus::Processos:
        ihm.atualizaMenu(&MenuProcessos::menuProcessos);
        break;
	}
}

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    Serial.println("Inicializado!");
   // inicializaMenuInicial();
    ihm.setup();//*/    
    MenuPrincipal::inicializaMenuInicial(trocaMenuPrincipal);
    MenuProcessos::inicializaMenuInicial(trocaMenuPrincipal);
    //ihm.atualizaMenu(&MenuProcessos::menuProcessos);/*
    ihm.atualizaMenu(&MenuPrincipal::menuPrincipal);//*/
}

// the loop function runs over and over again until power down or reset
void loop() {
	if(millis() % tLoop == 0)
        ihm.loop();
}
