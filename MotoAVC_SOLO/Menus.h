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

	MenuBase::Logo logoObras{};
	MenuMensagem menuEmObras;
	void iniciaMenuObras();

	MenuBase::Logo logoExec{};
	LinhaValor<float> linhas[3];
	static void atualizaCharExec();
	MenuLinhas menuExecucao;
	void iniciaMenuExec();

	float ref = 12.8, zm = 1.1;

public:
	MenusClass();
	void init(int tLoop);
	EnumMenus menuIhmIndex = Processos;
	EnumMenus menuIndexAnterior = Processos;
	MenuBase* menus[3]{};
};

extern MenusClass Menus;

#endif

