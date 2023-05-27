#pragma once

#include <LiquidCrystal.h>

namespace IHMv2
{
	struct AdjFloat
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

		void inc() const { inc(incremento); }

		void dec(const float decr) const { set(*valor - decr); }

		void dec() const { dec(incremento); }

		AdjFloat& operator = (const AdjFloat var)
		{
			valor = var.valor;
			min = var.min;
			max = var.max;
			incremento = var.incremento;
			return { *this };
		}
	};

	class LinhaBase
	{
	public:
		static String texto(const String& nome, const int varInt, const int nAlgarismos, const String& unidade, const bool imprimeValor)
		{
			auto txt = nome;
			for(auto i = 0; i < nAlgarismos; i++)
				txt += " ";
			if(contCaracteres(nome, unidade, nAlgarismos) < 16)
				txt += " ";
			txt += unidade;
			if(!imprimeValor)
				return txt;
			auto valor = textoInt(varInt, nAlgarismos);
			const auto index = nome.length();
			for(auto i = 0; i < valor.length() && index + i < 16; i++)
				txt.setCharAt(index + i, valor[i]);//*/
			return txt;
		}

		static String texto(const String& nome, const float varFloat, const int nDecimais, const int nAlgarismos, const String& unidade, const bool imprimeValor)
		{
			auto txt = nome;
			for(auto i = 0; i < nAlgarismos; i++)
				txt += " ";
			if(contCaracteres(nome, unidade, nAlgarismos) < 16)
				txt += " ";
			txt += unidade;
			if(!imprimeValor)
				return txt;
			auto valor = textoFloat(varFloat, nDecimais, nAlgarismos);
			const auto index = nome.length();
			for(auto i = 0; i < valor.length() && index + i < 16; i++)
				txt.setCharAt(index + i, valor[i]);//*/
			return txt;
		}

		static int contCaracteres(const String& n1, const String& n2, const int nAlg)
		{
			return n1.length() + n2.length() + nAlg;
		}

		static String textoInt(const int valor, const uint8_t nAlg)
		{
			auto txt = static_cast<String>(valor);
			while(txt.length() < nAlg)
				txt = " " + txt;
			return txt;
		}

		static String textoFloat(const float varFloat, const float nDecimais, const uint8_t nAlgarismos)
		{
			String txt = "";
			txt = String(varFloat, nDecimais);
			while(txt.length() < nAlgarismos)
				txt = " " + txt;
			if(txt.length() > nAlgarismos)
				return textoInt(varFloat, nAlgarismos);
			return txt;
		}
	};

	class LinhaGetValor : LinhaBase
	{
	public:
		/// <summary>
		/// Classe que cria uma linha de tela para uma variável int.
		/// </summary>
		/// <param name="nome"> Nome adotado pela variável.</param>
		/// <param name="varInt">Variável escolhida.</param>
		/// <param name="nAlgarismos">Número de algarismos máximo.</param>
		/// <param name="unidade">Unidade dimensional.</param>
		LinhaGetValor(const String& nome, int* varInt, const int nAlgarismos, const String unidade)
		{
			this->nome = nome;
			this->varInt = varInt;
			this->nAlgarismos = nAlgarismos;
			this->unidade = unidade;
		}

		/// <summary>
		/// Classe que cria uma linha de tela para uma variável float.
		/// </summary>
		/// <param name="nome">Nome adotado pela variável.</param>
		/// <param name="varGenerica">Variável escolhida.</param>
		/// <param name="nDecimais">Número de casas decimais máximo.</param>
		/// <param name="nAlgarismos">Número de algarismos máximo.</param>
		/// <param name="unidade">Unidade dimensional.</param>
		LinhaGetValor(const String& nome, float* varFloat, const int nDecimais, const int nAlgarismos, const String unidade)
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
			if(nCaracteres() < 16)
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

	private:
		String nome, unidade;
		float* varFloat = nullptr;
		unsigned char nDecimais = 1;
		int* varInt = nullptr;
		int nAlgarismos = 0;

		int nCaracteres() const
		{
			return contCaracteres(nome, unidade, nAlgarismos);
		}

		String printInt(const int valor) const
		{
			return textoInt(valor, nAlgarismos);
		}

		String printInt() const
		{
			return printInt(*varInt);
		}

		String printFloat() const
		{
			return textoFloat(*varFloat, nDecimais, nAlgarismos);
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
	};
	
	class LinhaSetFloat : LinhaBase
	{
	public:
		AdjFloat* varAdjFloat = nullptr;

		/// <summary>
		/// Classe que cria uma linha de tela para uma variável float.
		/// </summary>
		/// <param name="nome">Nome adotado pela variável.</param>
		/// <param name="varAdjFloat">Variável escolhida.</param>
		/// <param name="nDecimais">Número de casas decimais máximo.</param>
		/// <param name="nAlgarismos">Número de algarismos máximo.</param>
		/// <param name="unidade">Unidade dimensional.</param>
		LinhaSetFloat(const String& nome, AdjFloat* varAdjFloat, const int nDecimais, const int nAlgarismos, const String unidade)
		{
			this->nome = nome;
			this->varAdjFloat = varAdjFloat;
			varFloat = varAdjFloat->valor;
			this->nDecimais = nDecimais;
			this->nAlgarismos = nAlgarismos;
			this->unidade = unidade;
		}

		String texto(const bool imprimeValor) const
		{
			auto txt = nome;
			for(auto i = 0; i < nAlgarismos; i++)
				txt += " ";
			if(nCaracteres() < 16)
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

	private:
		String nome, unidade;
		float* varFloat = nullptr;
		unsigned char nDecimais = 1;
		int* varInt = nullptr;
		int nAlgarismos = 0;

		int nCaracteres() const
		{
			return contCaracteres(nome, unidade, nAlgarismos);
		}

		String printInt(const int valor) const
		{
			return textoInt(valor, nAlgarismos);
		}

		String printInt() const
		{
			return printInt(*varInt);
		}

		String printFloat() const
		{
			return textoFloat(*varFloat, nDecimais, nAlgarismos);
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
	};

}

namespace IHMv1_2
{
	struct AdjFloat
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
		
		AdjFloat& operator = (const AdjFloat var)
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
	public:
		AdjFloat* varAdjFloat = nullptr;
		const bool editavel;

		/// <summary>
		/// Classe que cria uma linha de tela para uma variável int.
		/// </summary>
		/// <param name="nome"> Nome adotado pela variável.</param>
		/// <param name="varInt">Variável escolhida.</param>
		/// <param name="nAlgarismos">Número de algarismos máximo.</param>
		/// <param name="unidade">Unidade dimensional.</param>
		Linha(const String& nome, int* varInt, const int nAlgarismos, const String unidade);

		/// <summary>
		/// Classe que cria uma linha de tela para uma variável float.
		/// </summary>
		/// <param name="nome">Nome adotado pela variável.</param>
		/// <param name="varGenerica">Variável escolhida.</param>
		/// <param name="nDecimais">Número de casas decimais máximo.</param>
		/// <param name="nAlgarismos">Número de algarismos máximo.</param>
		/// <param name="unidade">Unidade dimensional.</param>
		Linha(const String& nome, float* varFloat, const int nDecimais, const int nAlgarismos, const String unidade);

		/// <summary>
		/// Classe que cria uma linha de tela para uma variável float.
		/// </summary>
		/// <param name="nome">Nome adotado pela variável.</param>
		/// <param name="varAdjFloat">Variável escolhida.</param>
		/// <param name="nDecimais">Número de casas decimais máximo.</param>
		/// <param name="nAlgarismos">Número de algarismos máximo.</param>
		/// <param name="unidade">Unidade dimensional.</param>
		Linha(const String& nome, AdjFloat* varAdjFloat, const int nDecimais, const int nAlgarismos,
		      const String unidade);

		explicit Linha(const String& nome);

		static String texto(const String& nome, const int varInt, const int nAlgarismos, const String& unidade,
		                    const bool imprimeValor);

		static String texto(const String& nome, const float varFloat, const int nDecimais, const int nAlgarismos,
		                    const String& unidade, const bool imprimeValor);

		String texto(const bool imprimeValor) const;

	private:
		String nome, unidade;
		float* varFloat = nullptr;
		unsigned char nDecimais = 1;
		int* varInt = nullptr;
		int nAlgarismos = 0;


		static int contCaracteres(const String& n1, const String& n2, const int nAlg);

		int contCaracteres() const;

		static String printInt(const int valor, const uint8_t nAlg);

		String printInt(const int valor) const;

		String printInt() const;

		static String printFloat(const float varFloat, const float nDecimais, const uint8_t nAlgarismos);

		String printFloat() const;

		String printValor() const;
	};
	

	inline Linha::Linha(const String& nome, int* varInt, const int nAlgarismos, const String unidade): editavel(false)
	{
		this->nome = nome;
		this->varInt = varInt;
		this->nAlgarismos = nAlgarismos;
		this->unidade = unidade;
	}

	inline Linha::Linha(const String& nome, float* varFloat, const int nDecimais, const int nAlgarismos,
	                    const String unidade): editavel(false)
	{
		this->nome = nome;
		this->varFloat = varFloat;
		this->nDecimais = nDecimais;
		this->nAlgarismos = nAlgarismos;
		this->unidade = unidade;
	}

	inline Linha::Linha(const String& nome, AdjFloat* varAdjFloat, const int nDecimais, const int nAlgarismos,
	                    const String unidade): editavel(true)
	{
		this->nome = nome;
		this->varAdjFloat = varAdjFloat;
		varFloat = varAdjFloat->valor;
		this->nDecimais = nDecimais;
		this->nAlgarismos = nAlgarismos;
		this->unidade = unidade;
	}

	inline Linha::Linha(const String& nome): editavel(true)
	{
		this->nome = nome;
		this->unidade = unidade;
	}

	inline String Linha::texto(const String& nome, const int varInt, const int nAlgarismos, const String& unidade,
	                           const bool imprimeValor)
	{
		auto txt = nome;
		for (auto i = 0; i < nAlgarismos; i++)
			txt += " ";
		if (contCaracteres(nome, unidade, nAlgarismos) < 16)
			txt += " ";
		txt += unidade;
		if (!imprimeValor)
			return txt;
		auto valor = printInt(varInt, nAlgarismos);
		const auto index = nome.length();
		for (auto i = 0; i < valor.length() && index + i < 16; i++)
			txt.setCharAt(index + i, valor[i]); //*/
		return txt;
	}

	inline String Linha::texto(const String& nome, const float varFloat, const int nDecimais, const int nAlgarismos,
	                           const String& unidade, const bool imprimeValor)
	{
		auto txt = nome;
		for (auto i = 0; i < nAlgarismos; i++)
			txt += " ";
		if (contCaracteres(nome, unidade, nAlgarismos) < 16)
			txt += " ";
		txt += unidade;
		if (!imprimeValor)
			return txt;
		auto valor = printFloat(varFloat, nDecimais, nAlgarismos);
		const auto index = nome.length();
		for (auto i = 0; i < valor.length() && index + i < 16; i++)
			txt.setCharAt(index + i, valor[i]); //*/
		return txt;
	}

	inline String Linha::texto(const bool imprimeValor) const
	{
		auto txt = nome;
		for (auto i = 0; i < nAlgarismos; i++)
			txt += " ";
		if (contCaracteres() < 16)
			txt += " ";
		txt += unidade;
		if (!imprimeValor)
			return txt;
		auto valor = printValor();
		const auto index = nome.length();
		for (auto i = 0; i < valor.length() && index + i < 16; i++)
			txt.setCharAt(index + i, valor[i]); //*/
		return txt;
	}

	inline int Linha::contCaracteres(const String& n1, const String& n2, const int nAlg)
	{
		return n1.length() + n2.length() + nAlg;
	}

	inline int Linha::contCaracteres() const
	{
		return contCaracteres(nome, unidade, nAlgarismos);
	}

	inline String Linha::printInt(const int valor, const uint8_t nAlg)
	{
		auto txt = static_cast<String>(valor);
		while (txt.length() < nAlg)
			txt = " " + txt;
		return txt;
	}

	inline String Linha::printInt(const int valor) const
	{
		return printInt(valor, nAlgarismos);
	}

	inline String Linha::printInt() const
	{
		return printInt(*varInt);
	}

	inline String Linha::printFloat(const float varFloat, const float nDecimais, const uint8_t nAlgarismos)
	{
		String txt = "";
		txt = String(varFloat, nDecimais);
		while (txt.length() < nAlgarismos)
			txt = " " + txt;
		if (txt.length() > nAlgarismos)
			return printInt(varFloat, nAlgarismos);
		return txt;
	}

	inline String Linha::printFloat() const
	{
		return printFloat(*varFloat, nDecimais, nAlgarismos);
	}

	inline String Linha::printValor() const
	{
		if (varFloat != nullptr)
			return printFloat();
		if (varInt != nullptr)
			return printInt();
		String txt = "";
		for (auto i = 0; i < nAlgarismos; i++)
			txt = " " + txt;
		return txt;
	}

	class Ihm
	{
		const int encoderPinA = 2;
		const int encoderPinB = 4;
		const int SWITCH = 3;

		AdjFloat* varFloat;
		float* entrada{};
		volatile byte select{};
		Linha* linhas = nullptr;
		volatile byte telasLinha{};
		byte (*seqTelas)[2];
		byte nTelasLinha = 1;

		int pisca{};
		static Ihm* instancia;

		const int rs = A4, en = A5, d4 = A0, d5 = A1, d6 = A2, d7 = A3;
		LiquidCrystal lcd;
		
		Linha* linhaAtual(byte linha) const;
		bool linhaEditavel(byte linha) const;
		void handleEncoder();
		void handleSwitch();		


	public:
		Ihm(Linha* linhas, byte(* seqTelas)[2], int nLinhas);

		bool varAjustadas() const;
		void setup();
		void imprimeInterface();
	};

	Ihm* Ihm::instancia;

	inline Linha* Ihm::linhaAtual(const byte linha) const
	{
		return &linhas[seqTelas[telasLinha][linha]];
	}

	inline bool Ihm::linhaEditavel(const byte linha) const
	{
		return linhaAtual(linha)->editavel;
	}

	inline void Ihm::handleEncoder()
	{
		if(!select && nTelasLinha == 2)
			return;
		if(digitalRead(encoderPinB) == digitalRead(encoderPinA))
		{
			switch (select)
			{
				default:
					if(telasLinha == 0)
						telasLinha = nTelasLinha - 1;
					else
						telasLinha--;
					break;
				case 1:
					linhaAtual(0)->varAdjFloat->dec();
					break;
				case 2:
					linhaAtual(1)->varAdjFloat->dec();
					break;
			}
		}
		else
		{
			switch(select)
			{
				default:
					if(telasLinha == nTelasLinha - 1)
						telasLinha = 0;
					else
						telasLinha++;
					break;
				case 1:
					linhaAtual(0)->varAdjFloat->inc();
					break;
				case 2:
					linhaAtual(1)->varAdjFloat->inc();
					break;
			}
		}
	}

	inline void Ihm::handleSwitch()
	{
		if(!(linhaEditavel(0) || linhaEditavel(1)))
			return;
		if(select > 1 || select != 0 && !linhaEditavel(1))
			select = 0;
		else
		{
			select++;
			if(!linhaEditavel(0))
				select++;
		}

	}

	inline Ihm::Ihm(Linha* linhas, byte (*seqTelas)[2], const int nLinhas) : lcd(rs, en, d4, d5, d6, d7)
	{
		varFloat = linhas[0].varAdjFloat;
		this->linhas = linhas;
		this->seqTelas = seqTelas;
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

		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(linhaAtual(0)->texto(imprime || select != 1));
		lcd.setCursor(0, 1);
		lcd.print(linhaAtual(1)->texto(imprime || select != 2));
	}
}

namespace IHMv1
{
	struct AdjFloat
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

		void inc() const { inc(incremento); }

		void dec(const float decr) const { set(*valor - decr); }

		void dec() const { dec(incremento); }

		AdjFloat& operator = (const AdjFloat var)
		{
			valor = var.valor;
			min = var.min;
			max = var.max;
			incremento = var.incremento;
			return { *this };
		}
	};


	class Linha
	{
	public:
		/// <summary>
		/// Classe que cria uma linha de tela para uma variável int.
		/// </summary>
		/// <param name="nome"> Nome adotado pela variável.</param>
		/// <param name="varInt">Variável escolhida.</param>
		/// <param name="nAlgarismos">Número de algarismos máximo.</param>
		/// <param name="unidade">Unidade dimensional.</param>
		Linha(const String& nome, int* varInt, const int nAlgarismos, const String unidade)
		{
			this->nome = nome;
			this->varInt = varInt;
			this->nAlgarismos = nAlgarismos;
			this->unidade = unidade;
		}

		/// <summary>
		/// Classe que cria uma linha de tela para uma variável float.
		/// </summary>
		/// <param name="nome">Nome adotado pela variável.</param>
		/// <param name="varGenerica">Variável escolhida.</param>
		/// <param name="nDecimais">Número de casas decimais máximo.</param>
		/// <param name="nAlgarismos">Número de algarismos máximo.</param>
		/// <param name="unidade">Unidade dimensional.</param>
		Linha(const String& nome, float* varFloat, const int nDecimais, const int nAlgarismos, const String unidade)
		{
			this->nome = nome;
			this->varFloat = varFloat;
			this->nDecimais = nDecimais;
			this->nAlgarismos = nAlgarismos;
			this->unidade = unidade;
		}

		/// <summary>
		/// Classe que cria uma linha de tela para uma variável float.
		/// </summary>
		/// <param name="nome">Nome adotado pela variável.</param>
		/// <param name="varAdjFloat">Variável escolhida.</param>
		/// <param name="nDecimais">Número de casas decimais máximo.</param>
		/// <param name="nAlgarismos">Número de algarismos máximo.</param>
		/// <param name="unidade">Unidade dimensional.</param>
		Linha(const String& nome, AdjFloat* varAdjFloat, const int nDecimais, const int nAlgarismos, const String unidade)
		{
			this->nome = nome;
			this->varAdjFloat = varAdjFloat;
			varFloat = varAdjFloat->valor;
			this->nDecimais = nDecimais;
			this->nAlgarismos = nAlgarismos;
			this->unidade = unidade;
		}

		static String texto(const String& nome, const int varInt, const int nAlgarismos, const String& unidade, const bool imprimeValor)
		{
			auto txt = nome;
			for(auto i = 0; i < nAlgarismos; i++)
				txt += " ";
			if(contCaracteres(nome, unidade, nAlgarismos) < 16)
				txt += " ";
			txt += unidade;
			if(!imprimeValor)
				return txt;
			auto valor = printInt(varInt, nAlgarismos);
			const auto index = nome.length();
			for(auto i = 0; i < valor.length() && index + i < 16; i++)
				txt.setCharAt(index + i, valor[i]);//*/
			return txt;
		}

		static String texto(const String& nome, const float varFloat, const int nDecimais, const int nAlgarismos, const String& unidade, const bool imprimeValor)
		{
			auto txt = nome;
			for(auto i = 0; i < nAlgarismos; i++)
				txt += " ";
			if(contCaracteres(nome, unidade, nAlgarismos) < 16)
				txt += " ";
			txt += unidade;
			if(!imprimeValor)
				return txt;
			auto valor = printFloat(varFloat, nDecimais, nAlgarismos);
			const auto index = nome.length();
			for(auto i = 0; i < valor.length() && index + i < 16; i++)
				txt.setCharAt(index + i, valor[i]);//*/
			return txt;
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

	private:
		String nome, unidade;
		float* varFloat = nullptr;
		AdjFloat* varAdjFloat = nullptr;
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
	};

	class Ihm
	{
		const int encoderPinA = 2;
		const int encoderPinB = 4;
		const int SWITCH = 3;

		AdjFloat* varFloat;
		float* entrada{};
		volatile bool select{};
		Linha* linhas = nullptr;
		volatile byte telasLinha{};
		byte nTelasLinha = 1;

		int pisca{};
		static Ihm* instancia;

		const int rs = A4, en = A5, d4 = A0, d5 = A1, d6 = A2, d7 = A3;
		LiquidCrystal lcd;

		void handleEncoder();
		void handleSwitch();
		void printVarNameFloat(AdjFloat& var, bool imprimeVar);


	public:
		Ihm(float* var1, float* var2, float min, float max, float inc);
		Ihm(AdjFloat* var, float* var2);
		Ihm(AdjFloat* var, Linha* linhas, int nLinhas);

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
			else
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
			else
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
		varFloat = new AdjFloat{ var1, min, max, inc };
		entrada = var2;
	}

	inline Ihm::Ihm(AdjFloat* var, float* var2) : lcd(rs, en, d4, d5, d6, d7)
	{
		varFloat = var;
		entrada = var2;
	}

	inline Ihm::Ihm(AdjFloat* var, Linha* linhas, const int nLinhas) : lcd(rs, en, d4, d5, d6, d7)
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

		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(Linha::texto("(1) Ref:", *varFloat->valor, 1, 5, "V", imprime));
		lcd.setCursor(0, 1);
		if(linhas == nullptr)
			lcd.print(Linha::texto("   in:", *entrada, 1, 5, "V", true));
		else
			lcd.print(linhas[telasLinha].texto(true));


	}
}