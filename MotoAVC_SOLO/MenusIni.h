// MenusIni.h

#ifndef _MENUSINI_h
#define _MENUSINI_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Icones.h"
#include "MenuEnum.h"
#include "MenuMensagem.h"

namespace Menus
{
#ifdef TLOOP
    uint16_t tLoop = TLOOP; 
#else
    uint16_t tLoop = 50; // lembrar de ajustar no .ino
#endif

    EnumMenus::Menus menuIhmIndex = EnumMenus::Menus::Obras;
    EnumMenus::Menus menuIndexAnterior = EnumMenus::Menus::Principal;

    namespace MenuPrincipal
    {
        String enumModo[] = { "MOTOMAN","CNC", "Step&Dir" };
        uint8_t logoSize = 3, offsetLogo = 15 - logoSize - 1;
        MenuBase::Logo logos[] = {
	        {Icones::logoRobo, offsetLogo}, {Icones::logoCnc, offsetLogo - 1}, {Icones::logoStepDir, offsetLogo},
	        {Icones::logoLabsolda, offsetLogo}
        };
        uint8_t offset = -(logoSize + 1);
        MenuEnum menu("Modo", &menuIhmIndex, EnumMenus::Principal, 3, enumModo, logos, logoSize, offset, tLoop);
    }

    namespace MenuProcessos
    {
        String enumProcesso[] = { "TIG","TIG HF", " MIG Conv.", " MIG Puls." };
        byte(*logos[])[8] = { Icones::logoTig, Icones::logoTigHf, Icones::logoMigConv, Icones::logoMigPulse };
        uint8_t logoSize = 3, offset = logoSize + 1, offsetLogo = 2;
        MenuEnum menu("Processo", &menuIhmIndex, EnumMenus::Principal, 4, enumProcesso, logos, logoSize, offset, offsetLogo, tLoop);	    
    }

    namespace MenuEmObras
    {
        uint8_t logoSize = 3, offset = logoSize + 0, offsetLogo = 2;
        MenuBase::Logo logo[] = {
            {Icones::logoMartelo, offsetLogo}
        };
        MenuMensagem menu("EM", "OBRAS!", &menuIhmIndex, EnumMenus::Principal, logo, logoSize, offset, tLoop);
    }

    MenuBase* menus[3] = { &MenuPrincipal::menu , &MenuProcessos::menu, &MenuEmObras::menu };//*/	
}

#endif

