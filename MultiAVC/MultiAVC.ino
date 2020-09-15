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
Ihm ihm;



namespace MenuPrincipal
{
    Menu menuPrincipal;
    uint16_t modoOper;
    AdjGenerico<uint16_t> trocaModoOper = { &modoOper, 0, 3, 1};
    String nomeModos[4] = { "MOTOMAN","TIG HF", "TIG", "Modo MIG" };
    volatile byte select;
    Pisca pisca(5, 4);

    void menuPrincipalOnLoop()
    {
        if(select)
        {
            select--;
            if(!select)
            {
                trocaModoOper.dec();
                pisca.redefine(5,4);
            }
        }
        const auto imprime = pisca.aceso();
        //"0123456789012345"
        menuPrincipal.linhaSuperior = LinhaBase::textoCenter("Modo:");
        if(imprime)
            menuPrincipal.linhaInferior = LinhaBase::textoCenter(nomeModos[modoOper]);
        else
            menuPrincipal.linhaInferior = LinhaBase::limpa();
    }

    void menuPrincipalOnEncdrDec()
    {
        trocaModoOper.dec();
    }

    void menuPrincipalOnEncdrInc()
    {
        if(modoOper == trocaModoOper.max)
            modoOper = trocaModoOper.min;
        else
            trocaModoOper.inc();
    }

    inline void menuPrincipalOnClick()
    {
        select = 5;
        pisca.reseta(1,1);
    }

    void inicializaMenuInicial()
    {
        menuPrincipal.onLoop = menuPrincipalOnLoop;
        menuPrincipal.onEncdrDec = menuPrincipalOnEncdrDec;
        menuPrincipal.onEncdrInc = menuPrincipalOnEncdrInc;
        menuPrincipal.onClick = menuPrincipalOnClick;
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
	if(millis() % 200 == 0)
        ihm.loop();
}
