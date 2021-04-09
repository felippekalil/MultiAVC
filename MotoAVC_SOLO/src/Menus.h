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
	Portal portaisProc[4];
	MenuPortal menuProcessos;
	void iniciaMenuProc();

	Logo logoObras{};
	MenuMensagem menuEmObras;
	void iniciaMenuObras();

	Logo logoExec{};
	LinhaValor<float> linhas[7];
	uint16_t tPisca = 400; //ms
	uint16_t pisca = 0;
	void atualizaCharExec();
	MenuLinhas menuExecucao;
	void iniciaMenuExec();

public:
	MenusClass();
	void init(int tLoop);
	EnumMenus menuIhmIndex = Processos;
	EnumMenus menuIndexAnterior = Processos;
	MenuBase* menus[3]{};
	static MenusClass* pntrEstatico;

	uint8_t* linhasMenuExec();
};

extern MenusClass Menus;

#endif

