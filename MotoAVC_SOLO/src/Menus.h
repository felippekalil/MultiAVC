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
	MenuPortal menuProcessos;
	void iniciaMenuProc();

	MenuMensagem menuEmObras;
	void iniciaMenuObras();

	uint16_t tPisca = 400; //ms

	LinhaValor<float> linhasExec[4];
	Logo logoExecTig{};
	void atualizaCharExec(Logo &logo);
	MenuLinhas menuExecucaoTig;
	void iniciaMenuExecTig();
	Logo logoExecMig{};
	MenuLinhas menuExecucaoMig;
	void iniciaMenuExecMig();

	MenuLinhas menuConfig;
	void iniciaMenuConfig();//*/

public:
	MenusClass();
	void init(int tLoop);
	EnumMenus menuIhmIndex = Processos;
	EnumMenus menuIndexAnterior = Processos;
	MenuBase* menus[5]{};
	static MenusClass* pntrEstatico;

	uint8_t* linhasMenuExec();
};

extern MenusClass Menus;

#endif

