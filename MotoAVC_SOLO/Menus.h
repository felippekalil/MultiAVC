// Menus.h

#ifndef _MENUS_h
#define _MENUS_h

#include "Icones.h"
#include "MenuMensagem.h"
#include "MenuPortal.h"
#include "MenuLinhas.h"

class MenusClass
{
	uint16_t tLoop;


 public:
	void init();
	EnumMenus menuIhmIndex;
	EnumMenus menuIndexAnterior;
	MenuPortal menuProcessos;
	MenuMensagem menuEmObras;
};

extern MenusClass Menus;

#endif

