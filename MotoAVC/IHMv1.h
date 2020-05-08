#pragma once

#include <LiquidCrystal.h>

namespace IHMv1
{
	constexpr auto N_COLUNAS = 16;

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


		static int contCaracteres(const String& n1, const String& n2, const int nAlg) 
		{
			return n1.length() + n2.length() + nAlg;
		}

		int contCaracteres() const
		{
			return contCaracteres(nome, unidade, nAlgarismos);
		}

		static String printInt(const int valor, const uint8_t nAlg)
		{
			auto txt = static_cast<String>(valor);
			while(txt.length() < nAlg)
				txt = " " + txt;
			return txt;
		}

		String printInt(const int valor) const
		{
			return printInt(valor, nAlgarismos);
		}

		String printInt() const
		{
			return printInt(*varInt);
		}

		static String printFloat(const float varFloat, const float nDecimais, const uint8_t nAlgarismos)
		{
			String txt = "";
			txt = String(varFloat, nDecimais);
			while(txt.length() < nAlgarismos)
				txt = " " + txt;
			if(txt.length() > nAlgarismos)
				return printInt(varFloat, nAlgarismos);
			return txt;
		}

		String printFloat() const
		{
			return printFloat(*varFloat, nDecimais, nAlgarismos);
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
		Linha(const String& nome, int* varInt, const int nAlgarismos, const String unidade)
		{
			this->nome = nome;
			this->varInt = varInt;
			this->nAlgarismos = nAlgarismos;
			this->unidade = unidade;
		}
		Linha(const String& nome, float* varFloat, const int nDecimais, const int nAlgarismos, const String unidade)
		{
			this->nome = nome;
			this->varFloat = varFloat;
			this->nDecimais = nDecimais;
			this->nAlgarismos = nAlgarismos;
			this->unidade = unidade;
		}

		static String texto(const String& nome, const int varInt, const int nAlgarismos, const String& unidade, const bool imprimeValor)
		{
			auto txt = nome;
			for(auto i = 0; i < nAlgarismos; i++)
				txt += " ";
			if(contCaracteres(nome, unidade, nAlgarismos) < N_COLUNAS)
				txt += " ";
			txt += unidade;
			if(!imprimeValor)
			{
				while(txt.length() < N_COLUNAS)
					txt += " ";
				return txt;
			}
			auto valor = printInt(varInt, nAlgarismos);
			const auto index = nome.length();
			for(auto i = 0; i < valor.length() && index + i < N_COLUNAS; i++)
				txt.setCharAt(index + i, valor[i]);//*/
			if(txt.length() > N_COLUNAS)
				return txt.substring(0, N_COLUNAS - 1);
			while(txt.length() < N_COLUNAS)
				txt += " ";
			return txt;
		}

		static String texto(const String& nome, const float varFloat, const int nDecimais, const int nAlgarismos, const String& unidade, const bool imprimeValor)
		{
			auto txt = nome;
			for(auto i = 0; i < nAlgarismos; i++)
				txt += " ";
			if(contCaracteres(nome, unidade, nAlgarismos) < N_COLUNAS)
				txt += " ";
			txt += unidade;
			if(!imprimeValor)
			{
				while(txt.length() < N_COLUNAS)
					txt += " ";
				return txt;
			}
			auto valor = printFloat(varFloat, nDecimais, nAlgarismos);
			const auto index = nome.length();
			for(auto i = 0; i < valor.length() && index + i < N_COLUNAS; i++)
				txt.setCharAt(index + i, valor[i]);//*/
			if(txt.length() > N_COLUNAS)
				return txt.substring(0, N_COLUNAS - 1);
			while(txt.length() < N_COLUNAS)
				txt += " ";
			return txt;
		}

		String texto(const bool imprimeValor) const
		{
			auto txt = nome;
			for(auto i = 0; i < nAlgarismos; i++)
				txt += " ";
			if(contCaracteres() < N_COLUNAS)
				txt += " ";
			txt += unidade;
			if(!imprimeValor)
			{
				while(txt.length() < N_COLUNAS)
					txt += " ";
				return txt;
			}
			auto valor = printValor();
			const auto index = nome.length();
			for(auto i = 0; i < valor.length() && index + i < N_COLUNAS; i++)
				txt.setCharAt(index + i, valor[i]);//*/
			if(txt.length() > N_COLUNAS)
				return txt.substring(0, N_COLUNAS - 1);
			while(txt.length() < N_COLUNAS)
				txt += " ";
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
		Linha* linhas = nullptr;
		volatile byte telasLinha{};
		byte telasLinhaAnt{};
		float indexDeslocLinha = 0;
		byte nTelasLinha = 1;

		int pisca{};
		static Ihm* instancia;

		const int rs = A4, en = A5, d4 = A0, d5 = A1, d6 = A2, d7 = A3;
		LiquidCrystal lcd;

		void handleEncoder();
		void handleSwitch();		
		void printVarNameFloat(VarFloat& var, bool imprimeVar);


	public:
		Ihm(float* var1, float* var2, float min, float max, float inc);
		Ihm(VarFloat* var, float* var2);
		Ihm(VarFloat* var, Linha* linhas, int nLinhas);

		bool varAjustadas() const;
		void setup();
		void imprimeInterface();
	};

	Ihm* Ihm::instancia;

	inline void Ihm::handleEncoder()
	{
		if(!select && nTelasLinha == 1)
			return;
		if(digitalRead(encoderPinB) == digitalRead(encoderPinA))
		{
			if(select)
				varFloat->dec();
			else// if(telasLinha == telasLinhaAnt)
			{
				if(telasLinha == 0)
					telasLinha = nTelasLinha - 1;
				else
					telasLinha--;
			}
		}
		else
		{
			if(select)
				varFloat->inc();
			else //if(telasLinha == telasLinhaAnt)
			{
				if(telasLinha == nTelasLinha - 1)
					telasLinha = 0;
				else
					telasLinha++;
			}
		}
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

	inline Ihm::Ihm(VarFloat* var, Linha* linhas, const int nLinhas) : lcd(rs, en, d4, d5, d6, d7)
	{
		varFloat = var;
		this->linhas = linhas;
		nTelasLinha = nLinhas;
	}

	inline bool Ihm::varAjustadas() const
	{
		return select == 0;
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

		lcd.begin(N_COLUNAS, 2);
		lcd.print("    MotoAVC     ");
		lcd.setCursor(0, 1);
		lcd.print("     v1.0       ");
		//delay(1500);
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
		lcd.print(Linha::texto("  Ref:", *varFloat->valor, 1, 5, "V", imprime));
		lcd.setCursor(0, 1);
		if(linhas == nullptr)
			lcd.print(Linha::texto("   in:", *entrada, 1, 5, "V", true));
		else
		{
			if(telasLinha != telasLinhaAnt)
			{
				auto linhaNova = linhas[telasLinha].texto(true);
				auto linhaAnter = linhas[telasLinhaAnt].texto(true);
				String linhaTrans = "";
				for(auto i = 0; i < N_COLUNAS; i++)
					linhaTrans += " ";
				for(auto i = 0; i < N_COLUNAS; i++)
				{
					if(i < indexDeslocLinha)
						linhaTrans.setCharAt(i,linhaNova[N_COLUNAS - indexDeslocLinha + i]);
					else
						linhaTrans.setCharAt(i, linhaAnter[i - indexDeslocLinha]);

				}
				lcd.print(linhaTrans);
				indexDeslocLinha += 3;
				if(indexDeslocLinha >= N_COLUNAS)
				{
					indexDeslocLinha = 0;
					
					telasLinhaAnt = telasLinha;// > telasLinhaAnt ? telasLinhaAnt;
				}
			}
			else//*/
				lcd.print(linhas[telasLinha].texto(true));
		}


	}
}


namespace IHMv2
{// para ser continuado fururamente
	constexpr auto N_COLUNAS = 16;
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

		lcd.begin(N_COLUNAS, 2);
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