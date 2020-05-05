#pragma once

#include <LiquidCrystal.h>

namespace IHMv1
{
	struct VarFloat
	{	
		float* valor;
		float min, max, incremento;

		float get() const { return *valor; }

		void set(float vlr) const
		{
			if(vlr < min)
				vlr = min;
			if(vlr > max)
				vlr = max;
			*valor = vlr;
		}

		void inc(const float incr) const { set(*valor + incr); }

		void inc() const { inc(incremento);	}

		void dec(const float decr) const { set(*valor - decr); }

		void dec() const { dec(incremento); }
		
		VarFloat& operator = (const VarFloat var)
		{
			valor = var.valor;
			min = var.min;
			max = var.max;
			incremento = var.incremento;
			return {*this};
		}
	};

	class Ihm
	{
		const int encoderPinA = 2;
		const int encoderPinB = 4;
		const int SWITCH = 3;

		VarFloat* varFloat;
		float* entrada{};
		volatile bool select{};
		int pisca{};
		static Ihm* instancia;

		const int rs = A4, en = A5, d4 = A0, d5 = A1, d6 = A2, d7 = A3;
		LiquidCrystal lcd;

		void handleEncoder() const;

		void handleSwitch();
		void printVarNameFloat(VarFloat& var, bool imprimeVar);


	public:
		Ihm(float* var1, float* var2, float min, float max, float inc);
		Ihm(VarFloat* var, float* var2);

		void setup();

		void imprimeInterface();
	};

	Ihm* Ihm::instancia;

	inline void Ihm::handleEncoder() const
	{
		if(!select)
			return;
		if(digitalRead(encoderPinB) == digitalRead(encoderPinA))
			varFloat->dec();
		else
			varFloat->inc();
	}

	inline void Ihm::handleSwitch()
	{
		select = !select;
	}

	inline Ihm::Ihm(float* var1, float* var2, const float min, const float max, const float inc) : lcd(rs, en, d4, d5, d6, d7)
	{
		varFloat = new VarFloat{ var1, min, max, inc };
		entrada = var2;
	}

	inline Ihm::Ihm(VarFloat* var, float* var2) : lcd(rs, en, d4, d5, d6, d7)
	{
		varFloat = var;
		entrada = var2;
	}

	inline void Ihm::setup()
	{
		pinMode(LED_BUILTIN, OUTPUT);
		pinMode(encoderPinA, INPUT);
		digitalWrite(encoderPinA, HIGH);
		pinMode(encoderPinB, INPUT);
		digitalWrite(encoderPinB, HIGH);
		pinMode(SWITCH, INPUT);
		digitalWrite(SWITCH, HIGH);

		instancia = this;
		attachInterrupt(0, []() { instancia->handleEncoder(); }, CHANGE);
		attachInterrupt(1, []() { instancia->handleSwitch(); }, FALLING);

		lcd.begin(16, 2);
		lcd.print("    MotoAVC     ");
		lcd.setCursor(0, 1);
		lcd.print("     v1.0       ");

		delay(1500);
	}

	inline void Ihm::imprimeInterface()
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

		const auto valor = varFloat->get();

		Serial.print("Pos:");
		Serial.print(valor, 1);
		Serial.print("\tSwitch:");
		Serial.print(select, DEC);
		Serial.print("\tPisca:");
		Serial.print(pisca, DEC);
		Serial.print("\tImprime:");
		Serial.println(imprime, DEC);

		lcd.clear();
		lcd.setCursor(0, 0);

		lcd.print("Ref ");
		if(valor <= 10 - varFloat->incremento)
			lcd.print(" ");
		if(imprime)
			lcd.print(valor, 1);
		lcd.setCursor(10, 0);
		lcd.print("V");
		lcd.setCursor(0, 1);
		lcd.print(" In: ");
		if(*entrada <= 9.9)
			lcd.print(" ");
		lcd.print(*entrada, 1);
		lcd.setCursor(10, 1);
		lcd.print("V");// "olts");
	}
}


namespace IHMv2
{// início dos Menus Futuros
	struct VarFloat
	{
		String nome, unidade;
		float* valor;
		float min, max, incremento;

		float get() const { return *valor; }

		void set(float vlr) const
		{
			if(vlr < min)
				vlr = min;
			if(vlr > max)
				vlr = max;
			*valor = vlr;
		}

		void inc(const float incr) const { set(*valor + incr); }

		void inc() const { inc(incremento); }

		void dec(const float decr) const { set(*valor - decr); }

		void dec() const { dec(incremento); }

		VarFloat& operator = (const VarFloat var)
		{
			valor = var.valor;
			min = var.min;
			max = var.max;
			incremento = var.incremento;
			return { *this };
		}
	};

	class Ihm
	{
		const int encoderPinA = 2;
		const int encoderPinB = 4;
		const int SWITCH = 3;

		VarFloat* varFloat;
		float* entrada{};
		volatile bool select{};
		int pisca{};
		static Ihm* instancia;

		const int rs = A4, en = A5, d4 = A0, d5 = A1, d6 = A2, d7 = A3;
		LiquidCrystal lcd;

		void handleEncoder() const;

		void handleSwitch();
		void printVarNameFloat(VarFloat& var, bool imprimeVar);


	public:
		Ihm(float* var1, float* var2, float min, float max, float inc);
		Ihm(VarFloat* var, float* var2);

		void setup();

		void imprimeInterface();
	};

	Ihm* Ihm::instancia;

	inline void Ihm::handleEncoder() const
	{
		if(!select)
			return;
		if(digitalRead(encoderPinB) == digitalRead(encoderPinA))
			varFloat->dec();
		else
			varFloat->inc();
	}

	inline void Ihm::handleSwitch()
	{
		select = !select;
	}

	inline void Ihm::printVarNameFloat(VarFloat& var, const bool imprimeVar)
	{
		const auto valor = var.get();
		lcd.print(var.nome);
		if(valor <= 10 - var.incremento)
			lcd.print(" ");
		if(imprimeVar)
			lcd.print(valor, 1);
		lcd.setCursor(10, 0);
		lcd.print(var.unidade);
	}

	inline Ihm::Ihm(float* var1, float* var2, const float min, const float max, const float inc) : lcd(rs, en, d4, d5, d6, d7)
	{
		varFloat = nullptr;// new VarFloat{ "","", var1, min, max, inc };
		entrada = var2;
	}

	inline Ihm::Ihm(VarFloat* var, float* var2) : lcd(rs, en, d4, d5, d6, d7)
	{
		varFloat = var;
		entrada = var2;
	}

	inline void Ihm::setup()
	{
		pinMode(LED_BUILTIN, OUTPUT);
		pinMode(encoderPinA, INPUT);
		digitalWrite(encoderPinA, HIGH);
		pinMode(encoderPinB, INPUT);
		digitalWrite(encoderPinB, HIGH);
		pinMode(SWITCH, INPUT);
		digitalWrite(SWITCH, HIGH);

		instancia = this;
		attachInterrupt(0, []() { instancia->handleEncoder(); }, CHANGE);
		attachInterrupt(1, []() { instancia->handleSwitch(); }, FALLING);

		lcd.begin(16, 2);
		lcd.print("    MotoAVC     ");
		lcd.setCursor(0, 1);
		lcd.print("     v1.0       ");

		delay(1500);
	}

	inline void Ihm::imprimeInterface()
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

		const auto valor = varFloat->get();

		Serial.print("Pos:");
		Serial.print(valor, 1);
		Serial.print("\tSwitch:");
		Serial.print(select, DEC);
		Serial.print("\tPisca:");
		Serial.print(pisca, DEC);
		Serial.print("\tImprime:");
		Serial.println(imprime, DEC);

		lcd.clear();
		lcd.setCursor(0, 0);
		printVarNameFloat(*varFloat, imprime);
		lcd.setCursor(0, 1);
		lcd.print(" In: ");
		if(*entrada <= 9.9)
			lcd.print(" ");
		lcd.print(*entrada, 1);
		lcd.setCursor(10, 1);
		lcd.print("V");// "olts");
	}
}