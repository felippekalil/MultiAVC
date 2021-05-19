// Menus.h

#ifndef _MENUS_h
#define _MENUS_h

#include "Icones.h"
#include "MenuMensagem.h"
#include "MenuPortal.h"
#include "MenuLinhas.h"

class MenusClass
{
	uint16_t tLoop = 50;
	Portal portaisProc[3];
	MenuPortal menuProcessos;
	void iniciaMenuProc();

	Logo logoObras{};
	MenuMensagem menuEmObras;
	void iniciaMenuObras();

	uint16_t tPisca = 400; //ms
	uint16_t pisca = 0;

	Logo logoExec{};
	LinhaValor<float> linhasExec[4];
	void atualizaCharExec();
	MenuLinhas menuExecucao;
	void iniciaMenuExec();

	Logo logoConfig{};
	LinhaValor<float> linhasConfig[4];
	MenuLinhas menuConfig;
	void iniciaMenuConfig();//*/

public:
	MenusClass();
	void init(int tLoop);
	EnumMenus menuIhmIndex = Processos;
	EnumMenus menuIndexAnterior = Processos;
	MenuBase* menus[4]{};
	static MenusClass* pntrEstatico;

	uint8_t* linhasMenuExec();
};

extern MenusClass Menus;

#endif

