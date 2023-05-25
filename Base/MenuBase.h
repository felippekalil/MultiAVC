#pragma once
//#define MODO_CHAR
#ifndef _MENU_h
#define _MENU_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

enum EnumMenus
{
	Nada = -1,
	//Principal = 0,
	Processos = 0,
	Obras,
	Tig,
	Mig,
	MigAuto,
	Config,
	CountMenus
};

class Logo
{
public:
	const uint8_t* logoPtr{};
	uint8_t offset{};
	const uint8_t* charExtra{};
	uint8_t posCharExtra{};
	Logo() = default;
	Logo(const uint8_t* logo, const uint8_t off) : logoPtr(logo), offset(off) {}
	Logo(const uint8_t* logo, const uint8_t off, const uint8_t* extra, const uint8_t posExtra) : logoPtr(logo), offset(off), charExtra(extra), posCharExtra(posExtra) {}


	/*Logo& operator = (const Logo oldLogo)   // copy operator
	{
		this->logoPtr = oldLogo.logoPtr;
		this->offset = oldLogo.offset;
		this->charExtra = oldLogo.charExtra;
		this->posCharExtra = oldLogo.posCharExtra;
		return *this;
	}//*/

	/*	~Logo() //destructor
		{
			delete[] logoPtr;// = nullptr;
			delete[] charExtra;// = nullptr;
		}//*/

	Logo(const Logo& oldLogo) // copy constructor
	{
		this->logoPtr = oldLogo.logoPtr;
		this->offset = oldLogo.offset;
		this->charExtra = oldLogo.charExtra;
		this->posCharExtra = oldLogo.posCharExtra;
	}

	Logo& operator = (const Logo& var) = default;  // copy operator */

/*	Logo(Logo&& source) noexcept  // Move Constructor
	{
		this->logoPtr = source.logoPtr;
		this->offset = source.offset;
		this->charExtra = source.charExtra;
		this->posCharExtra = source.posCharExtra;
		source.logoPtr = nullptr;
		source.charExtra = nullptr;
	}

	Logo& operator = (Logo&& oldLogo) noexcept // Move operator
	{
		this->logoPtr = oldLogo.logoPtr;
		this->offset = oldLogo.offset;
		this->charExtra = oldLogo.charExtra;
		this->posCharExtra = oldLogo.posCharExtra;
		return *this;
	}//*/
};

class MenuBase
{
public:
	virtual ~MenuBase() = default;
	MenuBase() = default;

	EnumMenus* menuIhm = nullptr;
	EnumMenus menuAnterior = Processos;
	uint8_t apitar = 0;
	virtual void onMenuIni(void(*logoUpdate)(const Logo& logo)) = 0;
	virtual void atualizaLogo() = 0;
	virtual void onLoop() = 0;
	virtual void onEncdrDec(int mult = 1) = 0;
	virtual void onEncdrInc(int mult = 1) = 0;
	virtual void onClick() = 0;
	virtual void onVoltar() = 0;

#ifdef MODO_CHAR
	char* linhaSuperior = "";
	char* linhaInferior = "";
#else
	String linhaSuperior = "";
	String linhaInferior = "";
#endif
};

namespace MenuExtensoes
{
	class PiscaCiclo
	{
		byte interacao = 0;
	public:
		byte nAceso{};
		byte nApagado{};

		PiscaCiclo();
		PiscaCiclo(uint16_t aceso, uint16_t apagado, uint16_t tCiclo = 1);

		void reseta();

		void redefine(uint16_t aceso, uint16_t apagado, uint16_t tCiclo = 1);

		void reseta(uint16_t aceso, uint16_t apagado, uint16_t tCiclo = 1);

		bool aceso();
	};

	template <typename T>
	class AdjGenerico
	{
	public:
		AdjGenerico<T>() = default;
		AdjGenerico<T>(T& vlr, T mn, T mx, T inc, const bool clc)
		{
			valor = &vlr;
			min = mn;
			max = mx;
			incremento = inc;
			ciclico = clc;
		}

		T* valor = nullptr;
		T min = 0, max = 1, incremento = 1;
		bool ciclico = false;

		T get() const { return *valor; }

		void set(T vlr) const
		{
			const auto size = sizeof(vlr);
			if (size >= 4)
			{
				const uint8_t* temp = reinterpret_cast<uint8_t*>(&vlr);
				for (auto i = 0; i < size; i++)
				{
					if (temp[i] != 0xFF)
						break;
					if (i == size - 1)
						vlr = min;
				}
			}
			if (vlr < min)
				vlr = ciclico ? max : min;
			if (vlr > max)
				vlr = ciclico ? min : max;
			*valor = vlr;
		}

		void atualiza() const { set(*valor); }

		void inc(const int mult = 1) const
		{
			T ajuste = *valor + incremento * mult;
			if (ajuste > max
				|| (ajuste < min)) // caso deu a volta completa
				ajuste = ciclico ? min : max;
			set(ajuste);
		}

		void dec(const int mult = 1) const
		{
			T ajuste = *valor - incremento * mult;
			if (ajuste < min
				|| (ajuste > max)) // caso deu a volta completa
				ajuste = ciclico ? max : min;
			set(ajuste);
		}

		~AdjGenerico() //destructor
		{
			valor = nullptr;
		}

		AdjGenerico(const AdjGenerico& var) // copy constructor
		{
			valor = var.valor;
			min = var.min;
			max = var.max;
			incremento = var.incremento;
			ciclico = var.ciclico;
		}

		AdjGenerico& operator = (const AdjGenerico& var) = default;  // copy operator

		AdjGenerico(AdjGenerico&& source) noexcept  // Move Constructor
		{
			valor = source.valor;
			min = source.min;
			max = source.max;
			incremento = source.incremento;
			source.valor = nullptr;
		}

		AdjGenerico& operator = (AdjGenerico&& old) noexcept // Move operator
		{
			valor = old.valor;
			min = old.min;
			max = old.max;
			incremento = old.incremento;
			ciclico = old.ciclico;
			old.valor = nullptr;
			return { *this };
		}
	};

	class LinhaBase
	{
	public:
		static String texto(const String& nome, int varInt, int nAlgarismos, const String& unidade,
			bool imprimeValor);

		static String texto(const String& nome, float varFloat, int nDecimais, int nAlgarismos,
			const String& unidade, bool imprimeValor);

		static unsigned int contCaracteres(const String& n1, const String& n2, int nAlg);

		static String textoVar(int valor, uint8_t nAlg);

		static String textoVar(int valor, uint8_t nDecimais, uint8_t nAlg);

		static String textoVar(float varFloat, uint8_t nDecimais, uint8_t nAlgarismos);

		static String textoCenter(String texto, int8_t offset, int8_t max = 16);

		static String textoCenter(const String& texto);

		static String limpa();
	};

	template <typename T>
	class LinhaValor : LinhaBase
	{ // TODO: criar interface pra linhas de diferentes tipos
		String nome, unidade;
		T* var = nullptr;
		uint8_t nDecimais = 1;
		uint8_t nAlgarismos = 0;

		unsigned int nCaracteres() const;

		String printValor() const;

	public:
		LinhaValor() = default;

		// ------- READONLY ------
		/// <summary>
		/// Classe que cria uma linha de tela para uma vari�vel float.
		/// </summary>
		/// <param name="nome">Nome adotado pela vari�vel.</param>
		/// <param name="var">Vari�vel escolhida.</param>
		/// <param name="nDecimais">N�mero de casas decimais m�ximo.</param>
		/// <param name="nAlgarismos">N�mero de algarismos m�ximo.</param>
		/// <param name="unidade">Unidade dimensional.</param>
		LinhaValor(const String& nome, T& var, int nDecimais, int nAlgarismos, const String& unidade);

		/// <summary>
		/// Classe que cria uma linha de tela para uma vari�vel inteira.
		/// </summary>
		/// <param name="nome">Nome adotado pela vari�vel.</param>
		/// <param name="var">Vari�vel inteira escolhida.</param>
		/// <param name="nAlgarismos">N�mero de algarismos m�ximo.</param>
		/// <param name="unidade">Unidade dimensional.</param>
		LinhaValor(const String& nome, T& var, int nAlgarismos, const String& unidade);

		// ------- EDIT�VEL ------
		LinhaValor(const String& nome, AdjGenerico<T>& var, int nDecimais, int nAlgarismos, const String& unidade);
		LinhaValor(const String& nome, AdjGenerico<T>& var, int nAlgarismos, const String& unidade);

		AdjGenerico<T>* varAdjGen = nullptr;

		bool editavel() const;

		String texto(bool imprimeNome, bool imprimeValor) const;

		String texto(bool imprimeValor) const;

		String texto() const;
	};

	template <typename T>
	unsigned LinhaValor<T>::nCaracteres() const
	{
		return contCaracteres(nome, unidade, nAlgarismos);
	}

	template <typename T>
	String LinhaValor<T>::printValor() const
	{
		if (var != nullptr)
			return textoVar(*var, nDecimais, nAlgarismos);
		String txt = "";
		for (auto i = 0; i < nAlgarismos; i++)
			txt = " " + txt;
		return txt;
	}

	// ------ READONLY ------

	template <typename T>
	LinhaValor<T>::LinhaValor(const String& nome, T& var, const int nDecimais, const int nAlgarismos,
		const String& unidade)
	{
		this->nome = nome;
		this->var = &var;
		this->nDecimais = nDecimais;
		this->nAlgarismos = nAlgarismos;
		this->unidade = unidade;
	}

	template <typename T>
	LinhaValor<T>::LinhaValor(const String& nome, T& var, const int nAlgarismos, const String& unidade)
	{
		this->nome = nome;
		this->var = &var;
		this->nDecimais = 0;
		this->nAlgarismos = nAlgarismos;
		this->unidade = unidade;
	}

	// ------ EDIT�VEL -------

	template <typename T>
	LinhaValor<T>::LinhaValor(const String& nome, AdjGenerico<T>& var, int nDecimais, int nAlgarismos,
		const String& unidade)
	{
		this->nome = nome;
		this->varAdjGen = &var;
		this->var = var.valor;
		this->nDecimais = nDecimais;
		this->nAlgarismos = nAlgarismos;
		this->unidade = unidade;
	}

	template <typename T>
	LinhaValor<T>::LinhaValor(const String& nome, AdjGenerico<T>& var, int nAlgarismos, const String& unidade)
	{
		this->nome = nome;
		this->varAdjGen = &var;
		this->var = var.valor;
		this->nDecimais = 0;
		this->nAlgarismos = nAlgarismos;
		this->unidade = unidade;
	}

	template <typename T>
	bool LinhaValor<T>::editavel() const
	{
		return varAdjGen != nullptr;
	}

	template <typename T>
	String LinhaValor<T>::texto(const bool imprimeNome, const bool imprimeValor) const
	{
		auto txt = nome;
		if (!imprimeNome)
		{
			txt = "";
			for (auto i = 0; i < nome.length(); i++)
				txt += " ";
		}
		for (auto i = 0; i < nAlgarismos; i++)
			txt += " ";
		if (nCaracteres() < 16)
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

	template <typename T>
	String LinhaValor<T>::texto(const bool imprimeValor) const
	{
		return texto(true, imprimeValor);
	}

	template <typename T>
	String LinhaValor<T>::texto() const
	{
		return texto(true);
	}

}
#endif
