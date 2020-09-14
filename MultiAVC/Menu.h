#pragma once

#ifndef _MENUS_h
	#define _MENUS_h

class Menu
{
public:
	Menu() = default;;
	void(*onLoop)() = nullptr;
	void(*onEncdrDec)() = nullptr;
	void(*onEncdrInc)() = nullptr;
	void(*onClick)() = nullptr;
	void(*onVoltar)() = nullptr;
	char* linhaSuperior = "";
	char* linhaInferior = "";
};

#endif
