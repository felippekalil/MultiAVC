#pragma once

#include <LiquidCrystal.h>

namespace Interface
{
	constexpr auto ENCODER_PIN_A = 2 ;
	constexpr auto ENCODER_PIN_B = 4 ;
	constexpr auto SWITCH = 3;

	float* encoderPos;
	float* entrada;
	volatile bool select;
	int pisca;

	const int rs = A4, en = A5, d4 = A0, d5 = A1, d6 = A2, d7 = A3;
	LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

	inline void handleEncoder()
	{
		if(!select)
			return;
		if(digitalRead(ENCODER_PIN_B) == digitalRead(ENCODER_PIN_A))
			*encoderPos -= 0.1;
		else
			*encoderPos += 0.1;
	}

	inline void handleSwitch()
	{
		select = !select;
	}

	inline void setupInterface(float* encoder, float* in)
	{
		pinMode(LED_BUILTIN, OUTPUT);
		pinMode(ENCODER_PIN_A, INPUT);
		digitalWrite(ENCODER_PIN_A, HIGH);
		pinMode(ENCODER_PIN_B, INPUT);
		digitalWrite(ENCODER_PIN_B, HIGH);
		pinMode(SWITCH, INPUT);
		digitalWrite(SWITCH, HIGH);

		encoderPos = encoder;
		entrada = in;

		attachInterrupt(0, handleEncoder, CHANGE);
		attachInterrupt(1, handleSwitch, FALLING);

		lcd.begin(16, 2);
		lcd.print("    MotoAVC     ");
		lcd.setCursor(0, 1);
		lcd.print("     v1.0       ");

		delay(1500);
	}

	inline void imprimeInterface()
	{
		const auto espera = 3;
		if(select)
		{
			if(!pisca)
				pisca = espera - 1;
			pisca++;
		}
		else
			pisca = 0;
		const auto imprime = pisca == 0 || pisca % espera != 0;

		Serial.print("Pos:");
		Serial.print(*encoderPos, 1);
		Serial.print("\tSwitch:");
		Serial.print(select, DEC);
		Serial.print("\tPisca:");
		Serial.print(pisca, DEC);
		Serial.print("\tImprime:");
		Serial.println(imprime, DEC);

		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Ref: ");
		if(*encoderPos < 10)
			lcd.print(" ");
		if(!imprime)
		{
			lcd.setCursor(5, 0);
			lcd.print("      ");
		}
		lcd.print(*encoderPos, 1);
		lcd.setCursor(10, 0);
		lcd.print("Volts");
		lcd.setCursor(0, 1);
		lcd.print(" In: ");
		if(*entrada < 10)
			lcd.print(" ");
		lcd.print(*entrada, 1);
		lcd.setCursor(10, 1);
		lcd.print("Volts");
	}
}