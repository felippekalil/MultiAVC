// MenusIni.h

#ifndef _MENUSINI_h
#define _MENUSINI_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "MenuPortal.h"
#include "Icones.h"

namespace Menus
{
    uint16_t tLoop = 50; // lembrar de ajustar no .ino

    MenusEnum::Menus menuIhmIndex = MenusEnum::Menus::Principal;
    MenusEnum::Menus menuIndexAnterior = MenusEnum::Menus::Principal;

    namespace MenuPrincipal
    {
        String nomeEnums[] = { "MOTOMAN","CNC", "Step&Dir" };
        uint8_t logoSize = 3, offsetLogo = 15 - logoSize - 1;
        MenuBase::Logo logos[] = {
	        {Icones::logoRobo, offsetLogo}, {Icones::logoCnc, offsetLogo - 1}, {Icones::logoStepDir, offsetLogo},
	        {Icones::logoLabsolda, offsetLogo}
        };
        uint8_t offset = -(logoSize + 1);
        MenuPortal menu("Modo", &menuIhmIndex, MenusEnum::Principal, 3, nomeEnums, logos, logoSize, offset, tLoop);
    }

    namespace MenuProcessos
    {
        String nomeEnums[] = { "TIG","TIG HF", " MIG Conv.", " MIG Puls." };
        byte(*logos[])[8] = { Icones::logoTig, Icones::logoTigHf, Icones::logoMigConv, Icones::logoMigPulse };
        uint8_t logoSize = 3, offset = logoSize + 1, offsetLogo = 2;
        MenuPortal menu("Processo", &menuIhmIndex, MenusEnum::Principal, 4, nomeEnums, logos, logoSize, offset, offsetLogo, tLoop);	    
    }

    MenuBase* menus[2] = { &MenuPrincipal::menu , &MenuProcessos::menu };//*/	
}

#endif

