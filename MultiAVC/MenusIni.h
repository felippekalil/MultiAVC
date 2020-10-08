// MenusIni.h


#ifndef _MENUSINI_h
#define _MENUSINI_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Menu.h"
#include "IHMv2.h"
using namespace IHMv2;
constexpr uint16_t tLoop = 200;

namespace MenuPrincipal
{
    Ihm* ihm;
    Menu menuPrincipal;
    constexpr uint8_t nEnum = 3;
    String nomeModos[nEnum] = { "MOTOMAN","CNC", "Step&Dir" };
    uint16_t modoOper, modoOperAnt;
    AdjGenerico<uint16_t> trocaModoOper = { &modoOper, 0, nEnum - 1, 1 };
    volatile byte select;
    constexpr uint16_t tAceso = 800, tApagado = 500, tCiclo = tLoop;
    PiscaCiclo pisca(tAceso, tApagado, tCiclo);
    bool voltar = false;
    void(*updateLogo)(uint8_t logo[][8], uint8_t offset) = nullptr;

    constexpr uint8_t logoSize = 3;
    constexpr uint8_t offset = -(logoSize + 1);
    constexpr uint8_t offsetLogo = 15 - logoSize - 1;//*/

    inline void atualizaLogo()
    {
        if (updateLogo == nullptr)
            return;
        switch (modoOper)
        {
        case 0:
            updateLogo(logoRobo, offsetLogo);
            break;
        case 1:
            updateLogo(logoCnc, offsetLogo - 1);
            break;
        case 2:
            updateLogo(logoStepDir, offsetLogo);
            break;
        default:
            updateLogo(logoLabsolda, offsetLogo);
            break;
        }//*/
    }

    inline void menuPrincipalOnMenuIni(void(*logoUpdate)(uint8_t logo[][8], uint8_t offset))
    {
        updateLogo = logoUpdate;
        atualizaLogo();
    }

    inline void menuPrincipalOnEncdrDec()
    {
        trocaModoOper.dec();
        pisca.reseta();
    }

    inline void menuPrincipalOnEncdrInc()
    {
        if (modoOper == trocaModoOper.max)
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

    inline void menuPrincipalOnLoop()
    {
        if (select)
        {
            select--;
            if (!select)
            {
                if (voltar)
                {
                    voltar = false;
                    menuPrincipalOnEncdrDec();
                }
                else
                    //menuPrincipalOnEncdrInc();/*
                    *menuPrincipal.menuIhm = MenusEnum::Processos;
                pisca.redefine(tAceso, tApagado, tCiclo);
            }
        }
        const auto imprime = pisca.aceso();
        menuPrincipal.linhaSuperior = LinhaBase::textoCenter("Modo", offset);
        if (imprime)
            menuPrincipal.linhaInferior = LinhaBase::textoCenter(nomeModos[modoOper], offset);
        else
            menuPrincipal.linhaInferior = LinhaBase::limpa();
        if (modoOper != modoOperAnt)
            atualizaLogo();
        modoOperAnt = modoOper;
    }

    inline void inicializaMenuInicial(MenusEnum::Menus* menuAtual)
    {
        menuPrincipal.onMenuIni = menuPrincipalOnMenuIni;
        menuPrincipal.onLoop = menuPrincipalOnLoop;
        menuPrincipal.onEncdrDec = menuPrincipalOnEncdrDec;
        menuPrincipal.onEncdrInc = menuPrincipalOnEncdrInc;
        menuPrincipal.onClick = menuPrincipalOnClick;
        menuPrincipal.onVoltar = menuPrincipalOnVotar;
        menuPrincipal.menuIhm = menuAtual;
    }
}

namespace MenuProcessos
{
    Menu menuProcessos;
    constexpr uint8_t nEnum = 4;
    String nomeEnums[nEnum] = { "TIG","TIG HF", " MIG Conv.", " MIG Puls." };
    uint16_t enumerador, enumeradorAnt;
    AdjGenerico<uint16_t> trocaEnum = { &enumerador, 0, nEnum - 1, 1 };
    volatile byte select;
    constexpr uint16_t tAceso = 800, tApagado = 500, tCiclo = tLoop;
    // PiscaMs pisca(tAceso, tApagado);/*
    PiscaCiclo pisca(tAceso, tApagado, tCiclo);//*/
    bool voltar = false;
    void(*updateLogo)(uint8_t logo[][8], uint8_t offset) = nullptr;

    constexpr uint8_t logoSize = 3;
    constexpr uint8_t offset = logoSize + 1;
    constexpr uint8_t offsetLogo = 2;

    inline void atualizaLogo()
    {
        if (updateLogo == nullptr)
            return;
        switch (enumerador)
        {
        case 0:
            updateLogo(logoTig, offsetLogo);
            break;
        case 1:
            updateLogo(logoTigHf, offsetLogo);
            break;
        case 2:
            updateLogo(logoMigConv, offsetLogo);
            break;
        default:
            updateLogo(logoMigPulse, offsetLogo);
            break;
        }//*/
    }

    inline void menuPrincipalOnMenuIni(void(*logoUpdate)(uint8_t logo[][8], uint8_t offset))
    {
        updateLogo = logoUpdate;
        atualizaLogo();
    }

    inline void menuPrincipalOnEncdrDec()
    {
        trocaEnum.dec();
        pisca.reseta();
    }

    inline void menuPrincipalOnEncdrInc()
    {
        if (enumerador == trocaEnum.max)
            enumerador = trocaEnum.min;
        else
            trocaEnum.inc();
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
        //menuPrincipalOnClick();
    	*menuProcessos.menuIhm = MenusEnum::Principal;
    }

    inline void menuPrincipalOnLoop()
    {
        if (select)
        {
            select--;
            if (!select)
            {
                trocaEnum.inc();
                pisca.redefine(tAceso, tApagado, tCiclo);
            }
        }
        const auto imprime = pisca.aceso();
        menuProcessos.linhaSuperior = LinhaBase::textoCenter("Processo", offset);
        if (imprime)
            menuProcessos.linhaInferior = LinhaBase::textoCenter(nomeEnums[enumerador], offset);
        else
            menuProcessos.linhaInferior = LinhaBase::limpa();
        if (enumerador != enumeradorAnt)
            atualizaLogo();
        enumeradorAnt = enumerador;
    }

    inline void reset()
    {
        select = 0;
        voltar = false;
    }

    inline void inicializaMenuInicial(MenusEnum::Menus* menuAtual)
    {
        menuProcessos.onMenuIni = menuPrincipalOnMenuIni;
        menuProcessos.onLoop = menuPrincipalOnLoop;
        menuProcessos.onEncdrDec = menuPrincipalOnEncdrDec;
        menuProcessos.onEncdrInc = menuPrincipalOnEncdrInc;
        menuProcessos.onClick = menuPrincipalOnClick;
        menuProcessos.onVoltar = menuPrincipalOnVotar;
        menuProcessos.menuIhm = menuAtual;
    }
}
#endif

