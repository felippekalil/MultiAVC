// MenusIni.h

#include "Menu.h"

#ifndef _MENUSINI_h
#define _MENUSINI_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


//void(*onLoop)() = nullptr;
//void(*onEncdrDec)() = nullptr;
//void(*onEncdrInc)() = nullptr;
//void(*onClick)() = nullptr;
//void(*onVoltar)() = nullptr;
//String linhaSuperior = "";
//String linhaInferior = "";

Menu menuPrincipal;

//volatile byte select;
//int pisca;
//
//void menuPrincipalOnLoop()
//{
//	const auto espera = 3;
//	if(select)
//	{
//		if(!pisca)
//			pisca = espera - 1;
//		pisca++;
//	}
//	else
//		pisca = 0;
//	const auto imprime = pisca == 0 || pisca % espera != 0;
//								//"01234567890123456789"
//	if(select == 1 && pisca)
//		menuPrincipal.linhaSuperior = "                    ";
//	else
//		menuPrincipal.linhaSuperior = "     SUPERIOR       ";
//	if(select == 2 && pisca)
//		menuPrincipal.linhaInferior = "                    ";
//	else
//		menuPrincipal.linhaInferior = "     INFERIOR       ";
//}
//
//void menuPrincipalOnEncdrDec()
//{
//	
//}
//
//void menuPrincipalOnEncdrInc()
//{
//
//}
//
//inline void menuPrincipalOnClick()
//{
//	if(select > 1)
//		select = 0;
//	else
//		select++;
//}
//
//inline void menuPrincipalOnVoltar()
//{
//	if(select < 1)
//		select = 2;
//	else
//		select--;
//}
//
//void inicializaMenuInicial()
//{
//	menuPrincipal.onLoop = menuPrincipalOnLoop;
//	//menuPrincipal.onEncdrDec = menuPrincipalOnEncdrDec;
//	//menuPrincipal.onEncdrInc = menuPrincipalOnEncdrInc;
//	menuPrincipal.onClick = menuPrincipalOnClick;
//	menuPrincipal.onVoltar = menuPrincipalOnVoltar;
//}


#endif

