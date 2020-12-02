#pragma once
//#define MODO_CHAR
#ifndef _MENU_h
	#define _MENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace EnumMenus
{
	enum Menus
	{
		Principal = 0,
		Processos,
		Obras
	};
}

class MenuBase
{
public:
	virtual ~MenuBase() = default;
	MenuBase() = default;

	struct Logo
	{
		uint8_t *logoPtr;
		uint8_t offset;
	};

	virtual void onMenuIni(void(*logoUpdate)(Logo logo)) = 0;
	EnumMenus::Menus* menuIhm = nullptr;
	virtual void onLoop() = 0;
	virtual void onEncdrDec() = 0;
	virtual void onEncdrInc() = 0;
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
	/*class PiscaCiclo
	{
		byte interacao = 0;
	public:
		byte nAceso;
		byte nApagado;

		PiscaCiclo(const uint16_t aceso, const uint16_t apagado, const uint16_t tCiclo = 1)
		{
			nAceso = aceso / tCiclo;
			nApagado = apagado / tCiclo;
			if (nAceso < 1)
				nAceso = 1;
			if (nApagado < 1)
				nApagado = 1;
		}

		void reseta()
		{
			interacao = 0;
		}

		void redefine(const uint16_t aceso, const uint16_t apagado, const uint16_t tCiclo = 1)
		{
			nAceso = aceso / tCiclo;
			nApagado = apagado / tCiclo;
			if (nAceso < 1)
				nAceso = 1;
			if (nApagado < 1)
				nApagado = 1;
		}

		void reseta(const uint16_t aceso, const uint16_t apagado, const uint16_t tCiclo = 1)
		{
			redefine(aceso, apagado, tCiclo);
			reseta();
		}

		bool aceso()
		{
			interacao++;
			if (interacao < nAceso)
				return true;
			if (interacao < nAceso + nApagado)
				return false;
			interacao = 0;
			return true;
		}
	};*/


	class PiscaCiclo
	{
		byte interacao = 0;
	public:
		byte nAceso;
		byte nApagado;

		PiscaCiclo(uint16_t aceso, uint16_t apagado, uint16_t tCiclo = 1);

		void reseta();

		void redefine(uint16_t aceso, uint16_t apagado, uint16_t tCiclo = 1);

		void reseta(uint16_t aceso, uint16_t apagado, uint16_t tCiclo = 1);

		bool aceso();
	};

	template <typename T>
	struct AdjGenerico
	{
		T* valor;
		T min, max, incremento;

		T get() const { return *valor; }

		void set(T vlr) const
		{
			if (vlr < min)
				vlr = min;
			if (vlr > max)
				vlr = max;
			*valor = vlr;
		}

		void inc(const T incr) const { set(*valor + incr); }

		void inc() const { inc(incremento); }

		void dec(const T decr) const { set(*valor - decr); }

		void dec() const { dec(incremento); }

		AdjGenerico& operator = (const AdjGenerico var)
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
	{
		String nome, unidade;
		T* var = nullptr;
		uint8_t nDecimais = 1;
		uint8_t nAlgarismos = 0;

		unsigned int nCaracteres() const;

		String printValor() const;

	public:
		/// <summary>
		/// Classe que cria uma linha de tela para uma variável float.
		/// </summary>
		/// <param name="nome">Nome adotado pela variável.</param>
		/// <param name="var">Variável escolhida.</param>
		/// <param name="nDecimais">Número de casas decimais máximo.</param>
		/// <param name="nAlgarismos">Número de algarismos máximo.</param>
		/// <param name="unidade">Unidade dimensional.</param>
		LinhaValor(const String& nome, T* var, int nDecimais, int nAlgarismos, const String& unidade);

		LinhaValor(const String& nome, T& var, int nDecimais, int nAlgarismos, const String& unidade);

		/// <summary>
		/// Classe que cria uma linha de tela para uma variável float.
		/// </summary>
		/// <param name="nome">Nome adotado pela variável.</param>
		/// <param name="var">Variável inteira escolhida.</param>
		/// <param name="nAlgarismos">Número de algarismos máximo.</param>
		/// <param name="unidade">Unidade dimensional.</param>
		LinhaValor(const String& nome, T* var, int nAlgarismos, const String& unidade);

		LinhaValor(const String& nome, T& var, int nAlgarismos, const String& unidade);

		String texto(bool imprimeValor) const;

		String texto() const;
	};

	
}
#endif
