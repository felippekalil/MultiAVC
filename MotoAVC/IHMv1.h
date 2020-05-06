#pragma once

#include <LiquidCrystal.h>

namespace IHMv1
{
	//#define DEBOUNCE
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

	class Linha
	{
		String nome, unidade;
		float* varFloat = nullptr;
		unsigned char nDecimais = 1;
		int* varInt = nullptr;
		int nAlgarismos = 0;

		int contCaracteres() const
		{
			return nome.length() + unidade.length() + nAlgarismos;
		}

		String printInt(const int valor) const
		{
			auto txt = static_cast<String>(valor);
			while(txt.length() < nAlgarismos)
				txt = " " + txt;
			return txt;
		}

		String printInt() const
		{
			if(varInt == nullptr)
				return "";
			return printInt(*varInt);
		}

		String printFloat() const
		{
			String txt = "";
			if(varFloat == nullptr)
				return txt;
			txt = String(*varFloat, nDecimais);
			while(txt.length() < nAlgarismos)
				txt = " " + txt;
			if(txt.length() > nAlgarismos)
				return printInt(*varFloat);
			return txt;
		}

		String printValor() const
		{
			if(varFloat != nullptr)
				return printFloat();
			if(varInt != nullptr)
				return printInt();
			String txt = "";
			for(auto i = 0; i < nAlgarismos; i++)
				txt = " " + txt;
			return txt;
		}

	public:
		Linha(const String nome, int* varInt, const int nAlgarismos, const String unidade)
		{
			this->nome = nome;
			this->varInt = varInt;
			this->nAlgarismos = nAlgarismos;
			this->unidade = unidade;
		}
		Linha(const String nome, float* varFloat, const int nDecimais, const int nAlgarismos, const String unidade)
		{
			this->nome = nome;
			this->varFloat = varFloat;
			this->nDecimais = nDecimais;
			this->nAlgarismos = nAlgarismos;
			this->unidade = unidade;
		}

		String texto(const bool imprimeValor) const
		{
			auto txt = nome;
			for(auto i = 0; i < nAlgarismos; i++)
				txt += " ";
			if(contCaracteres() < 16)
				txt += " ";
			txt += unidade;
			if(!imprimeValor)
				return txt;
			auto valor = printValor();
			const auto index = nome.length();
			for(auto i = 0; i < valor.length() && index + i < 16; i++)
				txt.setCharAt(index + i, valor[i]);//*/
			return txt;
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

		volatile bool aguarda = false;
		long tInt = 0;

		const int rs = A4, en = A5, d4 = A0, d5 = A1, d6 = A2, d7 = A3;
		LiquidCrystal lcd;

		void handleEncoder() const;
		void handleSwitch();		
		void printVarNameFloat(VarFloat& var, bool imprimeVar);


	public:
		Ihm(float* var1, float* var2, float min, float max, float inc);
		Ihm(VarFloat* var, float* var2);

		void setup();
		void debounce(int wait);
		void imprimeInterface();
	};

	Ihm* Ihm::instancia;

	inline void Ihm::handleEncoder()
	#ifndef DEBOUNCE
		const
	#endif
	{
		if(!select || aguarda)
			return;
		if(digitalRead(encoderPinB) == digitalRead(encoderPinA))
			varFloat->dec();
		else
			varFloat->inc();//*/
		#ifdef DEBOUNCE
			aguarda = true;
		#endif

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
		//digitalWrite(encoderPinA, HIGH);
		pinMode(encoderPinB, INPUT);
		//digitalWrite(encoderPinB, HIGH);
		pinMode(SWITCH, INPUT);
		//digitalWrite(SWITCH, HIGH);

		instancia = this;
		attachInterrupt(0, []() { instancia->handleEncoder(); }, CHANGE);
		attachInterrupt(1, []() { instancia->handleSwitch(); }, FALLING);

		lcd.begin(16, 2);
		lcd.print("    MotoAVC     ");
		lcd.setCursor(0, 1);
		lcd.print("     v1.0       ");

		//delay(1500);
	}

	inline void Ihm::debounce(const int wait)
	{
		#ifndef DEBOUNCE
			return;
		#endif

		if(aguarda && tInt == 0)
			tInt = millis();
		else
			if(millis() >= tInt + wait && aguarda)
			{
				tInt = 0;
				aguarda = false;
				/*if(digitalRead(encoderPinB) == digitalRead(encoderPinA))
					varFloat->dec();
				else
					varFloat->inc();//*/
			}
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

		lcd.clear();
		lcd.setCursor(0, 0);
		const auto linha1 = new Linha("  Ref:", varFloat->valor, 1, 5, "V");
		lcd.print(linha1->texto(imprime));
		lcd.setCursor(0, 1);
		const auto linha2 = new Linha("   In:", entrada, 1, 5, "V");
		lcd.print(linha2->texto(true));
		delete linha1;
		delete linha2;

	}
}


namespace IHMv2
{// para ser continuado fururamente
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