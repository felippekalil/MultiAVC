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
    String nomeModos[5] = { "MOTOMAN","TIG HF", "TIG", "MIG Conv.", "MIG Puls." };
    uint16_t modoOper, modoOperAnt;
    AdjGenerico<uint16_t> trocaModoOper = { &modoOper, 0, 4, 1};
    volatile byte select;
    Pisca pisca(5, 4);
    void(*updateLogo)(uint8_t logo[][8], uint8_t nChar) = nullptr;


    void atualizaLogo()
    {        
        if (updateLogo == nullptr)
            return;
        updateLogo(logoLabsolda, modoOper * 2);
        /*switch (modoOper)
        {
        case 0:
            updateLogo(logoLabsolda, modoOper);
            break;
        }//*/
    }


    void menuPrincipalOnMenuIni(void(*logoUpdate)(uint8_t logo[][8], uint8_t nChar))
    {
        updateLogo = logoUpdate;
        atualizaLogo();
    }

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

        menuPrincipal.linhaSuperior = "    " + LinhaBase::textoCenter("Modo", 5);
        if(imprime)
            menuPrincipal.linhaInferior = "    " + LinhaBase::textoCenter(nomeModos[modoOper], 5);
        else
            menuPrincipal.linhaInferior = LinhaBase::limpa();
        if (modoOper != modoOperAnt)
            atualizaLogo();
        modoOperAnt = modoOper;
    }

    void menuPrincipalOnEncdrDec()
    {
        trocaModoOper.dec();
        pisca.reseta();
    }

    void menuPrincipalOnEncdrInc()
    {
        if(modoOper == trocaModoOper.max)
            modoOper = trocaModoOper.min;
        else
            trocaModoOper.inc();
        pisca.reseta();
    }

    inline void menuPrincipalOnClick()
    {
        select = 5;
        pisca.reseta(1,1);
    }

    void inicializaMenuInicial()
    {
        menuPrincipal.onMenuIni = menuPrincipalOnMenuIni;
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
