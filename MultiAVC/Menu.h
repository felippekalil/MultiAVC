#pragma once
//#define MODO_CHAR
#ifndef _MENUS_h
	#define _MENUS_h

#include "Arduino.h"

namespace MenusEnum
{
	enum Menus
	{
		Principal = 0,
		Processos
	};
}

class Menu
{
	static void vazio() {}
	static void vazio(void (*)(uint8_t[][8], uint8_t)) {}
	static void vazio(MenusEnum::Menus) {}
public:
	Menu() = default;
	void(*onMenuIni)(void(*logoUpdate)(uint8_t logo[][8], uint8_t offset)) = vazio;
	MenusEnum::Menus* menuIhm = nullptr;
	void(*onLoop)() = vazio;
	void(*onEncdrDec)() = vazio;
	void(*onEncdrInc)() = vazio;
	void(*onClick)() = vazio;
	void(*onVoltar)() = vazio;
#ifdef MODO_CHAR
	char* linhaSuperior = "";
	char* linhaInferior = "";
#else
	String linhaSuperior = "";
	String linhaInferior = "";
#endif
};

class MenuInterface
{
public:
	MenuInterface() = default;
	virtual void onMenuIni(void(*logoUpdate)(uint8_t logo[][8], uint8_t offset)) = 0;
	MenusEnum::Menus* menuIhm = nullptr;
	virtual void onLoop() = 0;
	virtual void onEncdrDec() = 0;
	virtual void onEncdrInc() = 0;
	virtual void onClick() = 0;
	virtual void onVoltar() = 0;
protected:
#ifdef MODO_CHAR
	char* linhaSuperior = "";
	char* linhaInferior = "";
#else
	String linhaSuperior = "";
	String linhaInferior = "";
#endif
};

//
//namespace MenuProcessos
//{
//    Menu menuProcessos;
//    constexpr uint8_t nEnum = 4;
//    String nomeEnums[nEnum] = { "TIG","TIG HF", " MIG Conv.", " MIG Puls." };
//    uint16_t enumerador, enumeradorAnt;
//    IHMv2::AdjGenerico<uint16_t> trocaEnum = { &enumerador, 0, nEnum - 1, 1 };
//    volatile byte select;
//    constexpr uint16_t tAceso = 800, tApagado = 500, tCiclo = tLoop;
//    // PiscaMs pisca(tAceso, tApagado);/*
//    PiscaCiclo pisca(tAceso, tApagado, tCiclo);//*/
//    bool voltar = false;
//    void(*updateLogo)(uint8_t logo[][8], uint8_t offset) = nullptr;
//
//    constexpr uint8_t logoSize = 3;
//    constexpr uint8_t offset = logoSize + 1;
//    constexpr uint8_t offsetLogo = 2;
//
//    inline void atualizaLogo()
//    {
//        if (updateLogo == nullptr)
//            return;
//        switch (enumerador)
//        {
//        case 0:
//            updateLogo(logoTig, offsetLogo);
//            break;
//        case 1:
//            updateLogo(logoTigHf, offsetLogo);
//            break;
//        case 2:
//            updateLogo(logoMigConv, offsetLogo);
//            break;
//        default:
//            updateLogo(logoMigPulse, offsetLogo);
//            break;
//        }//*/
//    }
//
//    inline void menuPrincipalOnMenuIni(void(*logoUpdate)(uint8_t logo[][8], uint8_t offset))
//    {
//        updateLogo = logoUpdate;
//        atualizaLogo();
//    }
//
//    inline void menuPrincipalOnEncdrDec()
//    {
//        trocaEnum.dec();
//        pisca.reseta();
//    }
//
//    inline void menuPrincipalOnEncdrInc()
//    {
//        if (enumerador == trocaEnum.max)
//            enumerador = trocaEnum.min;
//        else
//            trocaEnum.inc();
//        pisca.reseta();
//    }
//
//    inline void menuPrincipalOnClick()
//    {
//        select = 1000 / tCiclo;
//        pisca.reseta(150, 150, tCiclo);
//    }
//
//    inline void menuPrincipalOnVotar()
//    {
//        voltar = true;
//        //menuPrincipalOnClick();
//        menuProcessos.trocaMenu(MenusEnum::Principal);
//    }
//
//    inline void menuPrincipalOnLoop()
//    {
//        if (select)
//        {
//            select--;
//            if (!select)
//            {
//                trocaEnum.inc();
//                pisca.redefine(tAceso, tApagado, tCiclo);
//            }
//        }
//        const auto imprime = pisca.aceso();
//        menuProcessos.linhaSuperior = LinhaBase::textoCenter("Processo", offset);
//        if (imprime)
//            menuProcessos.linhaInferior = LinhaBase::textoCenter(nomeEnums[enumerador], offset);
//        else
//            menuProcessos.linhaInferior = LinhaBase::limpa();
//        if (enumerador != enumeradorAnt)
//            atualizaLogo();
//        enumeradorAnt = enumerador;
//    }
//
//    inline void reset()
//    {
//        select = 0;
//        voltar = false;
//    }
//
//    inline void inicializaMenuInicial(MenusEnum::Menus* menuAtual)
//    {
//        menuProcessos.onMenuIni = menuPrincipalOnMenuIni;
//        menuProcessos.onLoop = menuPrincipalOnLoop;
//        menuProcessos.onEncdrDec = menuPrincipalOnEncdrDec;
//        menuProcessos.onEncdrInc = menuPrincipalOnEncdrInc;
//        menuProcessos.onClick = menuPrincipalOnClick;
//        menuProcessos.onVoltar = menuPrincipalOnVotar;
//        menuProcessos.menuIhm = menuAtual;
//    }
//}
//
//class MenuBase
//{
//    volatile byte select;
//    IHMv2::PiscaCiclo pisca(tAceso, tApagado, tCiclo);//*/
//public:
//	MenuBase() = default;
//	virtual void onMenuIni(void(*logoUpdate)(uint8_t logo[][8], uint8_t offset));
//	virtual void trocaMenu(MenusEnum::Menus menuEnum);
//	virtual void onLoop();
//	virtual void onEncdrDec();
//	virtual void onEncdrInc();
//	virtual void onClick()
//	{
//        select = 1000 / tCiclo;
//        pisca.reseta(150, 150, tCiclo);
//	}
//	virtual void onVoltar();
//#ifdef MODO_CHAR
//	char* linhaSuperior = "";
//	char* linhaInferior = "";
//#else
//	String linhaSuperior = "";
//	String linhaInferior = "";
//#endif
//};
#endif
