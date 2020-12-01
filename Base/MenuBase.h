#pragma once
//#define MODO_CHAR
#ifndef _MENU_h
	#define _MENU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

namespace MenusEnum
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
	MenuBase() = default;

	struct Logo
	{
		uint8_t (*logo)[8];
		uint8_t offset;
	};

	virtual void onMenuIni(void(*logoUpdate)(Logo logo)) = 0;
	MenusEnum::Menus* menuIhm = nullptr;
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
	class PiscaCiclo
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
		static String texto(const String& nome, const int varInt, const int nAlgarismos, const String& unidade, const bool imprimeValor)
		{
			auto txt = nome;
			for (auto i = 0; i < nAlgarismos; i++)
				txt += " ";
			if (contCaracteres(nome, unidade, nAlgarismos) < 16)
				txt += " ";
			txt += unidade;
			if (!imprimeValor)
				return txt;
			auto valor = textoVar(varInt, nAlgarismos);
			const auto index = nome.length();
			for (auto i = 0; i < valor.length() && index + i < 16; i++)
				txt.setCharAt(index + i, valor[i]);//*/
			return txt;
		}

		static String texto(const String& nome, const float varFloat, const int nDecimais, const int nAlgarismos, const String& unidade, const bool imprimeValor)
		{
			auto txt = nome;
			for (auto i = 0; i < nAlgarismos; i++)
				txt += " ";
			if (contCaracteres(nome, unidade, nAlgarismos) < 16)
				txt += " ";
			txt += unidade;
			if (!imprimeValor)
				return txt;
			auto valor = textoVar(varFloat, nDecimais, nAlgarismos);
			const auto index = nome.length();
			for (auto i = 0; i < valor.length() && index + i < 16; i++)
				txt.setCharAt(index + i, valor[i]);//*/
			return txt;
		}

		static unsigned int contCaracteres(const String& n1, const String& n2, const int nAlg)
		{
			return n1.length() + n2.length() + nAlg;
		}

		static String textoVar(const int valor, const uint8_t nAlg)
		{
			auto txt = static_cast<String>(valor);
			while (txt.length() < nAlg)
				txt = " " + txt;
			return txt;
		}

		static String textoVar(const int valor, const uint8_t nDecimais, const uint8_t nAlg)
		{
			return textoVar(valor, nAlg);
		}

		static String textoVar(const float varFloat, const uint8_t nDecimais, const uint8_t nAlgarismos)
		{
			String txt = "";
			txt = String(varFloat, nDecimais);
			while (txt.length() < nAlgarismos)
				txt = " " + txt;
			if (txt.length() > nAlgarismos)
				return textoVar(static_cast<int>(varFloat), nAlgarismos);
			return txt;
		}

		static String textoCenter(String texto, const int8_t offset, const int8_t max = 16)
		{
			const auto lenght = texto.length();
			if (lenght > max - 2)
				return texto;
			int dif = (max - lenght) / 2 + offset / 2;
			String txt = " ";
			while (--dif > 0)
				txt += " ";
			return txt + texto;
		}

		static String textoCenter(const String& texto)
		{
			return textoCenter(texto, 0);
		}

		static String limpa()
		{
			return textoCenter("");
		}
	};

	template <typename T>
	class LinhaValor : LinhaBase
	{
		String nome, unidade;
		T* var = nullptr;
		uint8_t nDecimais = 1;
		uint8_t nAlgarismos = 0;

		unsigned int nCaracteres() const
		{
			return contCaracteres(nome, unidade, nAlgarismos);
		}

		String printValor() const
		{
			if (var != nullptr)
				return textoVar(*var, nDecimais, nAlgarismos);
			String txt = "";
			for (auto i = 0; i < nAlgarismos; i++)
				txt = " " + txt;
			return txt;
		}

	public:
		/// <summary>
		/// Classe que cria uma linha de tela para uma variável float.
		/// </summary>
		/// <param name="nome">Nome adotado pela variável.</param>
		/// <param name="var">Variável escolhida.</param>
		/// <param name="nDecimais">Número de casas decimais máximo.</param>
		/// <param name="nAlgarismos">Número de algarismos máximo.</param>
		/// <param name="unidade">Unidade dimensional.</param>
		LinhaValor(const String& nome, T* var, const int nDecimais, const int nAlgarismos, const String& unidade)
		{
			this->nome = nome;
			this->var = var;
			this->nDecimais = nDecimais;
			this->nAlgarismos = nAlgarismos;
			this->unidade = unidade;
		}

		LinhaValor(const String& nome, T& var, const int nDecimais, const int nAlgarismos, const String& unidade)
		{
			this->nome = nome;
			this->var = &var;
			this->nDecimais = nDecimais;
			this->nAlgarismos = nAlgarismos;
			this->unidade = unidade;
		}

		/// <summary>
		/// Classe que cria uma linha de tela para uma variável float.
		/// </summary>
		/// <param name="nome">Nome adotado pela variável.</param>
		/// <param name="var">Variável inteira escolhida.</param>
		/// <param name="nAlgarismos">Número de algarismos máximo.</param>
		/// <param name="unidade">Unidade dimensional.</param>
		LinhaValor(const String& nome, T* var, const int nAlgarismos, const String& unidade)
		{
			this->nome = nome;
			this->var = var;
			this->nDecimais = 0;
			this->nAlgarismos = nAlgarismos;
			this->unidade = unidade;
		}
		LinhaValor(const String& nome, T& var, const int nAlgarismos, const String& unidade)
		{
			this->nome = nome;
			this->var = &var;
			this->nDecimais = 0;
			this->nAlgarismos = nAlgarismos;
			this->unidade = unidade;
		}

		String texto(const bool imprimeValor) const
		{
			auto txt = nome;
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
				txt.setCharAt(index + i, valor[i]);//*/
			return txt;
		}

		String texto() const { return texto(true); }
	};
}

//class MenuBase
//{
//	static void vazio() {}
//	static void vazio(void (*)(uint8_t[][8], uint8_t)) {}
//	static void vazio(MenusEnum::Menus) {}
//public:
//	MenuBase() = default;
//	void(*onMenuIni)(void(*logoUpdate)(uint8_t logo[][8], uint8_t offset)) = vazio;
//	MenusEnum::Menus* menuIhmIndex = nullptr;
//	void(*onLoop)() = vazio;
//	void(*onEncdrDec)() = vazio;
//	void(*onEncdrInc)() = vazio;
//	void(*onClick)() = vazio;
//	void(*onVoltar)() = vazio;
//#ifdef MODO_CHAR
//	char* linhaSuperior = "";
//	char* linhaInferior = "";
//#else
//	String linhaSuperior = "";
//	String linhaInferior = "";
//#endif
//};
#endif
