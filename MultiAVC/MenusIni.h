// MenusIni.h

#ifndef _MENUSINI_h
#define _MENUSINI_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Menus.h"
#include "Icones.h"

namespace Menus
{
    uint16_t tLoop = 200;

    MenusEnum::Menus menuIhm = MenusEnum::Menus::Principal;
    MenusEnum::Menus menuAnterior = MenusEnum::Menus::Principal;

    String nomeModos[] = { "MOTOMAN","CNC", "Step&Dir" };
    uint8_t logoSize = 3, offsetLogo = 15 - logoSize - 1;
    MenuBase::Logo logos1[] = { {Icones::logoRobo, offsetLogo}, {Icones::logoCnc, offsetLogo - 1}, {Icones::logoStepDir, offsetLogo}, {Icones::logoLabsolda, offsetLogo} };
    uint8_t offset = -(logoSize + 1);
    MenuPortal menuInicial("Modo", &menuIhm, MenusEnum::Principal, 3, nomeModos, logos1, logoSize, offset, tLoop);

    String nomeEnums[] = { "TIG","TIG HF", " MIG Conv.", " MIG Puls." };
    byte(*logos2[])[8] = { Icones::logoTig, Icones::logoTigHf, Icones::logoMigConv, Icones::logoMigPulse };
    uint8_t logoSize2 = 3, offset2 = logoSize2 + 1, offsetLogo2 = 2;
    MenuPortal menuProcessos("Processo", &menuIhm, MenusEnum::Principal, 4, nomeEnums, logos2, logoSize2, offset2, offsetLogo2, tLoop);

    MenuBase* menus[2] = { &menuInicial , &menuProcessos };//*/	
}

#endif

