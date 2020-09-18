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
constexpr uint16_t tLoop = 200;
Ihm ihm(tLoop);

namespace MenuPrincipal
{
    Menu menuPrincipal;
    String nomeModos[5] = { "MOTOMAN","TIG HF", "TIG", "MIG Conv.", "MIG Puls." };
    uint16_t modoOper, modoOperAnt;
    AdjGenerico<uint16_t> trocaModoOper = { &modoOper, 0, 4, 1};
    volatile byte select;
    constexpr uint16_t tAceso = 800, tApagado = 500, tCiclo = tLoop;
   // PiscaMs pisca(tAceso, tApagado);/*
    PiscaCiclo pisca(tAceso, tApagado, tCiclo);//*/
    bool voltar = false;
    void(*updateLogo)(uint8_t logo[][8], uint8_t nChar) = nullptr;


    void atualizaLogo()
    {        
        if (updateLogo == nullptr)
            return;
        switch (modoOper)
        {
        case 0:
            updateLogo(logoRobo, 8);
            break;
        default:
            updateLogo(logoLabsolda, 8);
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
                if (voltar)
                {
                    voltar = false;
                    trocaModoOper.dec();
                }
                else
                    trocaModoOper.inc();
                pisca.redefine(tAceso, tApagado, tCiclo);
            }
        }
        const auto imprime = pisca.aceso();

        menuPrincipal.linhaSuperior = LinhaBase::textoCenter("Modo:", 2);
        if(imprime)
            menuPrincipal.linhaInferior = LinhaBase::textoCenter(nomeModos[modoOper], 2);
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
        select = 1000 / tCiclo;
        pisca.reseta(150, 150, tCiclo);
    }

    inline void menuPrincipalOnVotar()
    {
        voltar = true;
        menuPrincipalOnClick();
    }

    void inicializaMenuInicial()
    {
        menuPrincipal.onMenuIni = menuPrincipalOnMenuIni;
        menuPrincipal.onLoop = menuPrincipalOnLoop;
        menuPrincipal.onEncdrDec = menuPrincipalOnEncdrDec;
        menuPrincipal.onEncdrInc = menuPrincipalOnEncdrInc;
        menuPrincipal.onClick = menuPrincipalOnClick;
        menuPrincipal.onVoltar = menuPrincipalOnVotar;
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
	if(millis() % tLoop == 0)
        ihm.loop();
}
