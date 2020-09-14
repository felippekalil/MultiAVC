/*
 Name:		MultiAVC.ino
 Created:	9/11/2020 3:09:05 PM
 Author:	Felippe Kalil Mendonça
*/
#include <LiquidCrystal.h>
//#include "MenusIni.h"
#include "IHMv2.h"
using namespace IHMv2;
Ihm ihm;

namespace MenuPrincipal
{
    //void(*onLoop)() = nullptr;
    //void(*onEncdrDec)() = nullptr;
    //void(*onEncdrInc)() = nullptr;
    //void(*onClick)() = nullptr;
    //void(*onVoltar)() = nullptr;
    //String linhaSuperior = "";
    //String linhaInferior = "";

    Menu menuPrincipal;

    volatile byte select;
    int pisca;
    
    void menuPrincipalOnLoop()
    {
    	const auto espera = 3;
    	if(select)
    	{
    		if(!pisca)
    			pisca = espera - 1;
    		pisca++;
    	}
    	else
    		pisca = 0;
    	const auto imprime = pisca == 0 || pisca % espera != 0;
    									//"0123456789012345"
        if(select == 1 && !imprime)
            menuPrincipal.linhaSuperior = "                ";
        else
            menuPrincipal.linhaSuperior = "    SUPERIOR    ";
        if(select == 2 && !imprime)
            menuPrincipal.linhaInferior = "                ";
        else
            menuPrincipal.linhaInferior = "    INFERIOR    ";
    }
    
    void menuPrincipalOnEncdrDec()
    {
    	
    }
    
    void menuPrincipalOnEncdrInc()
    {
    
    }
    
    inline void menuPrincipalOnClick()
    {
    	if(select > 1)
    		select = 0;
    	else
    		select++;
    }
    
    inline void menuPrincipalOnVoltar()
    {
    	if(select < 1)
    		select = 2;
    	else
    		select--;
    }
    
    void inicializaMenuInicial()
    {
    	menuPrincipal.onLoop = menuPrincipalOnLoop;
    	menuPrincipal.onEncdrDec = menuPrincipalOnEncdrDec;
    	menuPrincipal.onEncdrInc = menuPrincipalOnEncdrInc;
    	menuPrincipal.onClick = menuPrincipalOnClick;
    	menuPrincipal.onVoltar = menuPrincipalOnVoltar;
    }
}

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    Serial.println("Inicializado!");
   // inicializaMenuInicial();
    ihm.setup();//*/
    MenuPrincipal::inicializaMenuInicial();
    ihm.atualizaMenu(&MenuPrincipal::menuPrincipal);
}

// the loop function runs over and over again until power down or reset
void loop() {
	if(millis() % 300 == 0)
        ihm.loop();
}
