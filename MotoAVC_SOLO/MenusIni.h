// MenusIni.h

#ifndef _MENUSINI_h
#define _MENUSINI_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Icones.h"
#include "MenuMensagem.h"
#include "MenuPortal.h"
#include "MenuLinhas.h"

namespace Menus
{
#ifdef TLOOP
    uint16_t tLoop = TLOOP; 
#else
    uint16_t tLoop = 50; // lembrar de ajustar no .ino
#endif

    EnumMenus menuIhmIndex = Processos;
    EnumMenus menuIndexAnterior = Processos;

    //namespace MenuPrincipal
    //{
    //    uint8_t logoSize = 3, offsetLogo = 15 - logoSize - 1;
    //    Portal portalModo[] = {
    //        {"MOTOMAN",  {reinterpret_cast<uint8_t*>(&Icones::logoRobo), offsetLogo}, EnumMenus::Processos},
    //        { "CNC", {reinterpret_cast<uint8_t*>(&Icones::logoCnc), offsetLogo - 1}, EnumMenus::Obras},
    //        {"Step&Dir", {reinterpret_cast<uint8_t*>(&Icones::logoStepDir), offsetLogo}, EnumMenus::Obras}
    //    };
    //    uint8_t offset = -(logoSize + 1);
    //    MenuPortal menu("Modo", &menuIhmIndex, EnumMenus::Principal, 3, portalModo, logoSize, offset, tLoop);
    //}

    namespace MenuProcessos
    {
        uint8_t logoSize = 3, offset = logoSize + 1, offsetLogo = 2;
        Portal portaisProc[] = {
        	{"TIG HF", {reinterpret_cast<uint8_t*>(&Icones::logoTig), offsetLogo, reinterpret_cast<uint8_t*>(&Icones::charRaio), 2}, EnumMenus::Execucao},
            {"TIG", {reinterpret_cast<uint8_t*>(&Icones::logoTig), offsetLogo}, EnumMenus::Obras},
            {" MIG Conv.", {reinterpret_cast<uint8_t*>(&Icones::logoMig), offsetLogo, reinterpret_cast<uint8_t*>(&Icones::charCurto), 2 }, EnumMenus::Obras},
            {" MIG Puls.", {reinterpret_cast<uint8_t*>(&Icones::logoMig), offsetLogo, reinterpret_cast<uint8_t*>(&Icones::charPulse), 2 }, EnumMenus::Obras }};
        MenuPortal menu("Processo", &menuIhmIndex, EnumMenus::Processos, 4, portaisProc, logoSize, offset, tLoop);
    }

    namespace MenuEmObras
    {
        uint8_t logoSize = 3, offset = logoSize + 0, offsetLogo = 2;
        MenuBase::Logo logo = { reinterpret_cast<uint8_t*>(&Icones::logoMartelo), offsetLogo };
        MenuMensagem menu("EM", "OBRAS!", &menuIhmIndex, logo, logoSize, offset, tLoop);
    }


    //namespace MenuEmObras
    //{
    //    uint8_t logoSize = 3, offset = logoSize + 0, offsetLogo = 2;
    //    MenuBase::Logo logo;// = { reinterpret_cast<uint8_t*>(&Icones::logoMartelo), offsetLogo };
    //    MenuMensagem menu;// ("EM", "OBRAS!", &menuIhmIndex, logo, logoSize, offset, tLoop);

    //    inline void iniciaMenu()
    //    {
    //        logo = { reinterpret_cast<uint8_t*>(&Icones::logoMartelo), offsetLogo };
    //        menu.ini("EM", "OBRAS!", &menuIhmIndex, logo, logoSize, offset, tLoop);
    //    }
    //}

    namespace MenuExecucao
    {
        using namespace MenuExtensoes;
        MenuLinhas menu;
        float ref = 12.8, zm = 1.1; 
        MenuBase::Logo logo;
        AdjGenerico<float> referencia = { &ref, 0.1, 99.9, 0.1, false };
        LinhaValor<float> linhaRef = {"Ref: ", referencia, 1, 4, "V" };
        AdjGenerico<float> zonaMorta = { &zm, 0.1, 99.9, 0.1, false };
        LinhaValor<float> linhaZM = { "Z.M: ", zonaMorta, 1, 4, "V" };
        LinhaValor<float> linhaIn = { " In: ", ref, 1, 4, "V" };
        LinhaValor<float> linhas[] = { linhaRef, // 0  // TODO: criar interface base pra linhas de diferentes tipos
        								linhaZM,
										linhaIn}; // 1
        void atualizaCharLogo()
        {
	        
        }

        inline void iniciaMenu()
        {
            const auto logoSize = 3, offset = logoSize + 1, offsetLogo = 0;
            logo = { reinterpret_cast<uint8_t*>(&Icones::logoTig), offsetLogo };
            menu.inicializaMenu(&menuIhmIndex, logo, linhas, 3, atualizaCharLogo, logoSize, offset, tLoop);
        }
    }

    void iniciaMenus()
    {
        MenuExecucao::iniciaMenu();
    }

    MenuBase* menus[] = 
    { 
    	&MenuProcessos::menu, 
    	&MenuEmObras::menu,
        &MenuExecucao::menu
    };//*/	
}

#endif

