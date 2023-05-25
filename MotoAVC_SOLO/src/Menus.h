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
	LinhaValor<float> linhasExecAuto[5];
	Logo logoExecTig{};
	Logo logoExecMigAuto{};
	MenuLinhas menuExecucaoTig;
	Logo logoExecMig{};
	MenuLinhas menuExecucaoMig;
	MenuLinhas menuExecucaoMigAuto;
	void atualizaCharExec(Logo &logo);
	void iniciaLinhasExec();
	void iniciaLinhasExecAuto();
	void iniciaMenuExecTig();
	void iniciaMenuExecMig();

	MenuLinhas menuConfig;
	void iniciaMenuConfig();//*/

public:
	MenusClass();
	void init(int tLoop);
	EnumMenus menuIhmIndex = Processos;
	EnumMenus menuIndexAnterior = Processos;
	MenuBase* menus[CountMenus]{};
	static MenusClass* pntrEstatico;

	uint8_t* linhasMenuExec();
};

extern MenusClass Menus;

#endif

