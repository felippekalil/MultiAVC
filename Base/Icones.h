#pragma once
#include "Arduino.h"

#ifndef _ICONES_CLASS_H
	#define _ICONES_CLASS_H

class Icones
{
public:
	static const uint8_t PROGMEM FIM[];
	static const uint8_t PROGMEM LOGO_LABSOLDA[][8];
	static const uint8_t PROGMEM LOGO_ROBO[][8];
	static const uint8_t PROGMEM LOGO_TIG[][8];
	static const uint8_t PROGMEM LOGO_MIG[][8];
	static const uint8_t PROGMEM LOGO_CONFIG[][8];
	static const uint8_t PROGMEM LOGO_MARTELO[][8];
	static const uint8_t PROGMEM CHAR_RAIO[8];
	static const uint8_t PROGMEM CHAR_CURTO[8];
	static const uint8_t PROGMEM CHAR_PULSE[8];
	static const uint8_t PROGMEM CHAR_OK[8];
	static const uint8_t PROGMEM CHAR_NONE[8];
	static const uint8_t PROGMEM CHAR_UP[8];
	static const uint8_t PROGMEM CHAR_DWN[8];
};

#endif
