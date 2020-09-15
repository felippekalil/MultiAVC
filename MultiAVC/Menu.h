#pragma once
//#define MODO_CHAR
#ifndef _MENUS_h
	#define _MENUS_h

#include "Arduino.h"

class Menu
{
	static void vazio(){}
public:
	Menu() = default;
	void(*onLoop)() = vazio;
	void(*onEncdrDec)() = vazio;
	void(*onEncdrInc)() = vazio;
	void(*onClick)() = vazio;
	void(*onVoltar)() = vazio;
#ifdef MODO_CHAR
	char* linhaSuperior = "";
	char* linhaInferior = "";
#else
	String linhaSuperior = "";
	String linhaInferior = "";
#endif
};

#endif
