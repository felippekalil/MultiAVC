#pragma once

#include <LiquidCrystal.h>
#include "Menu.h"
#ifndef _IHMV2_H
	#define _IHMV2_H

namespace Icones
{
	// usar B100000 como identificador de final
	byte fim[] = {
		B100000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000 
	};

	byte logoLabsolda[][8] = { {
		B00000,
		B00000,
		B00000,
		B00000,
		B00111,
		B00100,
		B00100,
		B00100
	},{
		B00000,
		B00001,
		B00111,
		B01111,
		B11110,
		B01100,
		B01100,
		B00100
	},{
		B00000,
		B11000,
		B11100,
		B00010,
		B00001,
		B00000,
		B01000,
		B01100
	},{
		B00000,
		B00000,
		B00000,
		B00000,
		B11100,
		B00100,
		B00100,
		B00100
	},{
		B00100,
		B00100,
		B00100,
		B00111,
		B00000,
		B00000,
		B00000,
		B00000
	},{
		B00110,
		B00010,
		B00000,
		B10000,
		B01000,
		B00111,
		B00011,
		B00000
	},{
		B00100,
		B00110,
		B00110,
		B01111,
		B11110,
		B11100,
		B10000,
		B00000/*
	},{
		B00100,
		B00010,
		B00010,
		B00111,
		B11110,
		B11100,
		B11000,
		B00000//*/
	},{
		B00100,
		B00100,
		B00100,
		B11100,
		B00000,
		B00000,
		B00000,
		B00000
	}
	};

	byte logoRobo[][8] = { {
		B00000,
		B00000,
		B00000,
		B00111,
		B01111,
		B01111,
		B01111,
		B01111
	},{
		B00011,
		B00111,
		B00111,
		B11111,
		B11000,
		B10000,
		B00000,
		B00000
	},{
		B00000,
		B00000,
		B00000,
		B10000,
		B11110,
		B01001,
		B01000,
		B01100
	},{
		B00111,
		B00111,
		B00111,
		B01111,
		B01111,
		B01111,
		B11111,
		B11111
	},{
		B00000,
		B00000,
		B00000,
		B10000,
		B10000,
		B10000,
		B11000,
		B11000
	},{
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000
	},{
		B100000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000
	}
	};
	
	byte logoCnc[][8] = { {
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000
	},{
		B00000,
		B00000,
		B00100,
		B00100,
		B01110,
		B01110,
		B01110,
		B01110
	},{
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000
	},{
		B00000,
		B00000,
		B00000,
		B00111,
		B01100,
		B01000,
		B11111,
		B11111
	},{
		B01110,
		B00100,
		B00000,
		B11111,
		B00000,
		B00000,
		B11111,
		B11111
	},{
		B00000,
		B00000,
		B00000,
		B11100,
		B00100,
		B00010,
		B11111,
		B11111
	},{
		B100000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000
	}
	};
	
	byte logoCncOld[][8] = { {
		B00000,
		B11111,
		B10000,
		B10000,
		B10110,
		B10111,
		B10110,
		B10110
	},{
		B00000,
		B11100,
		B00100,
		B00100,
		B01110,
		B01110,
		B01110,
		B01110
	},{
		B00000,
		B00000,
		B00000,
		B00000,
		B01100,
		B11100,
		B01100,
		B01100
	},{
		B10110,
		B10110,
		B10110,
		B11111,
		B01100,
		B01000,
		B11111,
		B11111
	},{
		B01110,
		B00100,
		B00000,
		B11111,
		B00000,
		B00000,
		B11111,
		B11111
	},{
		B01100,
		B01100,
		B01100,
		B11100,
		B00100,
		B00010,
		B11111,
		B11111
	},{
		B100000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000
	}
	};

	byte logoStepDir[][8] = { {
		B00000,
		B01110,
		B01010,
		B01010,
		B01010,
		B01010,
		B11011,
		B00000
	},{
		B00000,
		B01110,
		B01010,
		B01010,
		B01010,
		B01010,
		B11011,
		B00000
	},{
		B00000,
		B01110,
		B01010,
		B01010,
		B01010,
		B01010,
		B11011,
		B00000
	},{
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B11111,
		B00000
	},{
		B00000,
		B00111,
		B00100,
		B00100,
		B00100,
		B00100,
		B11100,
		B00000
	},{
		B00000,
		B11111,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000
	},{
		B100000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000
	}
	};

	byte logoTig[][8] = { {
		B11000,
		B11100,
		B01110,
		B00111,
		B00011,
		B00001,
		B00001,
		B00000
	},{
		B00000,
		B00000,
		B00000,
		B00000,
		B11000,
		B11100,
		B11110,
		B11111
	},{
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000
	},{
		B00001,
		B00011,
		B01111,
		B11111,
		B11110,
		B11100,
		B11000,
		B10000
	},{
		B11111,
		B11111,
		B10011,
		B00001,
		B00000,
		B00000,
		B00000,
		B00000
	},{
		B10000,
		B11000,
		B11100,
		B11100,
		B11110,
		B00110,
		B00001,
		B00000
	},{
		B100000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000
	}
	};

	byte logoTigHf[][8] = { {
		B11000,
		B11100,
		B01110,
		B00111,
		B00011,
		B00001,
		B00001,
		B00000
	},{
		B00000,
		B00000,
		B00000,
		B00000,
		B11000,
		B11100,
		B11110,
		B11111
	},{
		B00111,
		B01110,
		B01100,
		B11111,
		B00110,
		B00100,
		B01000,
		B00000
	},{
		B00001,
		B00011,
		B01111,
		B11111,
		B11110,
		B11100,
		B11000,
		B10000
	},{
		B11111,
		B11111,
		B10011,
		B00001,
		B00000,
		B00000,
		B00000,
		B00000
	},{
		B10000,
		B11000,
		B11100,
		B11100,
		B11110,
		B00110,
		B00001,
		B00000
	},{
		B100000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000
	}
	};
	
	byte logoMigConv[][8] = { {
		B00000,
		B00000,
		B11100,
		B11111,
		B00011,
		B00001,
		B00001,
		B00001
	},{
		B00000,
		B00000,
		B00000,
		B00000,
		B11100,
		B11110,
		B11111,
		B11111
	},{
		B00010,
		B00100,
		B01100,
		B11111,
		B00110,
		B01110,
		B11100,
		B00000
	},{
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000
	},{
		B11111,
		B01111,
		B00111,
		B00001,
		B00000,
		B00000,
		B00000,
		B00000
	},{
		B10000,
		B11000,
		B11100,
		B11110,
		B11110,
		B11100,
		B01010,
		B00001
	},{
		B100000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000
	}
	};

	byte logoMigPulse[][8] = { {
		B00000,
		B00000,
		B11100,
		B11111,
		B00011,
		B00001,
		B00001,
		B00001
	},{
		B00000,
		B00000,
		B00000,
		B00000,
		B11100,
		B11110,
		B11111,
		B11111
	},{
		B00000,
		B00000,
		B01110,
		B01010,
		B01010,
		B01010,
		B11011,
		B00000
	},{
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000
	},{
		B11111,
		B01111,
		B00111,
		B00001,
		B00000,
		B00000,
		B00000,
		B00000
	},{
		B10000,
		B11000,
		B11100,
		B11110,
		B11110,
		B11100,
		B01010,
		B00001
	},{
		B100000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000,
		B00000
	}
	};
}

namespace IHMv2
{
	using namespace Icones;

	inline void pause()
	{
		while (1) {}
	}

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
			if(vlr < min)
				vlr = min;
			if(vlr > max)
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
			for(auto i = 0; i < nAlgarismos; i++)
				txt += " ";
			if(contCaracteres(nome, unidade, nAlgarismos) < 16)
				txt += " ";
			txt += unidade;
			if(!imprimeValor)
				return txt;
			auto valor = textoVar(varInt, nAlgarismos);
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
			auto valor = textoVar(varFloat, nDecimais, nAlgarismos);
			const auto index = nome.length();
			for(auto i = 0; i < valor.length() && index + i < 16; i++)
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
			while(txt.length() < nAlg)
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
			while(txt.length() < nAlgarismos)
				txt = " " + txt;
			if(txt.length() > nAlgarismos)
				return textoVar(static_cast<int>(varFloat), nAlgarismos);
			return txt;
		}

		static String textoCenter(String texto, const int8_t offset, const int8_t max = 16)
		{
			const auto lenght = texto.length();
			if(lenght > max - 2)
				return texto;
			int dif = (max - lenght) / 2 + offset/2;
			String txt = " ";
			while(--dif > 0)
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
			if(var != nullptr)
				return textoVar(*var, nDecimais, nAlgarismos);
			String txt = "";
			for(auto i = 0; i < nAlgarismos; i++)
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

		String texto() const { return texto(true); }
	};

	class Ihm
	{
		const int encoderPinA = 2;
		const int encoderPinB = 4;
		const int buzzer = 5;
		uint16_t tempoBuzzer;
		const int SWITCH = 3;
		uint16_t tempoVoltar;
		const uint16_t duracaoBuzzer = 200;
		const uint16_t duracaoVoltar = 600;

		const int rs = A4, en = A5, d4 = A0, d5 = A1, d6 = A2, d7 = A3;
		LiquidCrystal lcd;
		static Ihm* instancia;
		volatile uint16_t apitaBuzzer = 0, clickVoltar = 0;
		uint8_t nCharLogo = 0, offsetLogo = 0;

		void apitarBuzzer()
		{
			apitaBuzzer = tempoBuzzer;
		}

		void handleEncoder()
		{
			apitarBuzzer();
			if(digitalRead(encoderPinB) == digitalRead(encoderPinA))//dec
				menuAtual->onEncdrDec();
			else //inc
				menuAtual->onEncdrInc();
		}

		void handleSwitch()
		{
			if(digitalRead(SWITCH))
				clickVoltar = tempoVoltar;
			else
			{
				apitarBuzzer();
				if(clickVoltar) // se ainda está contando
				{
					clickVoltar = 0;
					menuAtual->onClick();
				}
			}
		}

		void imprimeInterface()
		{
			lcd.clear(); 
			lcd.setCursor(0, 0);
			lcd.print(menuAtual->linhaSuperior);
			lcd.setCursor(0, 1);
			lcd.print(menuAtual->linhaInferior);
			imprimeLogo();
		}

		Menu* menuAtual{};

	public:
		explicit Ihm(const uint16_t tLoop) : lcd(rs, en, d4, d5, d6, d7)
		{
			tempoBuzzer = duracaoBuzzer / tLoop;
			tempoVoltar = duracaoVoltar / tLoop;
		}

		explicit Ihm(Menu* menu, const uint16_t tLoop) : lcd(rs, en, d4, d5, d6, d7)
		{
			tempoBuzzer = duracaoBuzzer / tLoop;
			tempoVoltar = duracaoVoltar / tLoop;
			atualizaMenu(menu);
		}

		void atualizaMenu(Menu* menu)
		{
			menuAtual = menu;
			nCharLogo = 0;
			menuAtual->onMenuIni([](const Menu::Logo logo) {instancia->createLogo(logo);});
		}

		bool varAjustadas() const;

		void imprimeLogo()
		{
			lcd.setCursor(offsetLogo, 0);
			for (uint8_t i = 0; i < nCharLogo; i++)
			{
				if(i == nCharLogo / 2)
					lcd.setCursor(offsetLogo, 1);
				lcd.write(static_cast<uint8_t>(i));
			}
		}

		void createChar(const uint8_t index, uint8_t customChar[])
		{
			lcd.createChar(index, customChar);
		}

		void createLogo(Menu::Logo logo)
		{
			uint8_t i;
			for (i = 0; i < 8; i++)
			{
				if (logo.logo[i][0] >= B100000)
					break;
				createChar(i, logo.logo[i]);
			}
			nCharLogo = i;
			this->offsetLogo = logo.offset;
		}
		
		void telaInicialLabsolda()
		{
			imprimeLogo();
			lcd.setCursor(5, 0);
			lcd.print(" LABSOLDA");
			const String inst = "Instituto de Soldagem e Mecatronica";
			const auto iniLcd = 5;
			const auto lenght = 15 - iniLcd;
			const auto lastLcd = inst.length() - lenght;
			delay(1000);
			for(auto i = 0; i < lastLcd; i++)
			{
				lcd.setCursor(iniLcd, 1);
				lcd.print(inst.substring(i, i + lenght + 1));
				delay(200);
			}
		}

		void setup()
		{
			pinMode(LED_BUILTIN, OUTPUT);
			pinMode(buzzer, OUTPUT);
			pinMode(encoderPinA, INPUT);
			pinMode(encoderPinB, INPUT);
			pinMode(SWITCH, INPUT);

			instancia = this;
			attachInterrupt(0, []() { instancia->handleEncoder(); }, CHANGE);
			attachInterrupt(1, []() { instancia->handleSwitch(); }, CHANGE);

			lcd.begin(16, 2);
			const Menu::Logo logoLab = { logoLabsolda, 1 };
			createLogo(logoLab);

			//telaInicialLabsolda();

			lcd.clear();
			imprimeLogo();

			lcd.setCursor(5, 0);
			lcd.print(" MultiAVC");
			lcd.setCursor(5, 1);
			lcd.print("   v1.0");
			delay(1500);
		}

		void loop()
		{
			if(apitaBuzzer)
			{
				apitaBuzzer--;
				digitalWrite(buzzer, true);
			}
			else
				digitalWrite(buzzer, false);
			if(clickVoltar)
			{
				if(clickVoltar == 1)
				{
					apitarBuzzer();
					menuAtual->onVoltar();
				}
				clickVoltar--;
			}
			menuAtual->onLoop();
			imprimeInterface();
		}
	};

	Ihm* Ihm::instancia;

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
		Linha(const String& nome, int* varInt, const int nAlgarismos, const String& unidade) : editavel(false)
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
		/// <param name="var">Variável escolhida.</param>
		/// <param name="nDecimais">Número de casas decimais máximo.</param>
		/// <param name="nAlgarismos">Número de algarismos máximo.</param>
		/// <param name="unidade">Unidade dimensional.</param>
		Linha(const String& nome, float* varFloat, const int nDecimais, const int nAlgarismos, const String& unidade) : editavel(false)
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
		Linha(const String& nome, AdjFloat* varAdjFloat, const int nDecimais, const int nAlgarismos, const String& unidade) : editavel(true)
		{
			this->nome = nome;
			this->varAdjFloat = varAdjFloat;
			varFloat = varAdjFloat->valor;
			this->nDecimais = nDecimais;
			this->nAlgarismos = nAlgarismos;
			this->unidade = unidade;
		}

		Linha(const String& nome) : editavel(true)
		{
			this->nome = nome;
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
		/// <param name="var">Variável escolhida.</param>
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

#endif