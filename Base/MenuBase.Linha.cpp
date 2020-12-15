#include "MenuBase.h"


namespace MenuExtensoes // LINHA BASE	
{
	String LinhaBase::texto(const String& nome, const int varInt, const int nAlgarismos, const String& unidade,
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
		auto valor = textoVar(varInt, nAlgarismos);
		const auto index = nome.length();
		for (auto i = 0; i < valor.length() && index + i < 16; i++)
			txt.setCharAt(index + i, valor[i]); //*/
		return txt;
	}

	String LinhaBase::texto(const String& nome, const float varFloat, const int nDecimais, const int nAlgarismos,
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
		auto valor = textoVar(varFloat, nDecimais, nAlgarismos);
		const auto index = nome.length();
		for (auto i = 0; i < valor.length() && index + i < 16; i++)
			txt.setCharAt(index + i, valor[i]); //*/
		return txt;
	}

	unsigned LinhaBase::contCaracteres(const String& n1, const String& n2, const int nAlg)
	{
		return n1.length() + n2.length() + nAlg;
	}

	String LinhaBase::textoVar(const int valor, const uint8_t nAlg)
	{
		auto txt = static_cast<String>(valor);
		while (txt.length() < nAlg)
			txt = " " + txt;
		return txt;
	}

	String LinhaBase::textoVar(const int valor, const uint8_t nDecimais, const uint8_t nAlg)
	{
		return textoVar(valor, nAlg);
	}

	String LinhaBase::textoVar(const float varFloat, const uint8_t nDecimais, const uint8_t nAlgarismos)
	{
		String txt = "";
		txt = String(varFloat, nDecimais);
		while (txt.length() < nAlgarismos)
			txt = " " + txt;
		if (txt.length() > nAlgarismos)
			return textoVar(static_cast<int>(varFloat), nAlgarismos);
		return txt;
	}

	String LinhaBase::textoCenter(String texto, const int8_t offset, const int8_t max)
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

	String LinhaBase::textoCenter(const String& texto)
	{
		return textoCenter(texto, 0);
	}

	String LinhaBase::limpa()
	{
		return textoCenter("");
	}
}

namespace MenuExtensoes // LINHA VALOR
{
	//template <typename T>
	//unsigned LinhaValor<T>::nCaracteres() const
	//{
	//	return contCaracteres(nome, unidade, nAlgarismos);
	//}

	//template <typename T>
	//String LinhaValor<T>::printValor() const
	//{
	//	if (var != nullptr)
	//		return textoVar(*var, nDecimais, nAlgarismos);
	//	String txt = "";
	//	for (auto i = 0; i < nAlgarismos; i++)
	//		txt = " " + txt;
	//	return txt;
	//}

	//// ------ READONLY ------

	//template <typename T>
	//LinhaValor<T>::LinhaValor(const String& nome, T& var, const int nDecimais, const int nAlgarismos,
	//	const String& unidade) 
	//{
	//	this->nome = nome;
	//	this->var = &var;
	//	this->nDecimais = nDecimais;
	//	this->nAlgarismos = nAlgarismos;
	//	this->unidade = unidade;
	//}

	//template <typename T>
	//LinhaValor<T>::LinhaValor(const String& nome, T& var, const int nAlgarismos, const String& unidade)
	//{
	//	this->nome = nome;
	//	this->var = &var;
	//	this->nDecimais = 0;
	//	this->nAlgarismos = nAlgarismos;
	//	this->unidade = unidade;
	//}

	//// ------ EDITÁVEL -------

	//template <typename T>
	//LinhaValor<T>::LinhaValor(const String& nome, AdjGenerico<T>& var, int nDecimais, int nAlgarismos,
	//	const String& unidade)
	//{
	//	this->nome = nome;
	//	this->varAdjGen = &var;
	//	this->var = var->get();
	//	this->nDecimais = nDecimais;
	//	this->nAlgarismos = nAlgarismos;
	//	this->unidade = unidade;
	//}

	//template <typename T>
	//LinhaValor<T>::LinhaValor(const String& nome, AdjGenerico<T>& var, int nAlgarismos, const String& unidade)
	//{
	//	this->nome = nome;
	//	this->varAdjGen = &var;
	//	this->var = var->get();
	//	this->nDecimais = 0;
	//	this->nAlgarismos = nAlgarismos;
	//	this->unidade = unidade;
	//}

	//template <typename T>
	//bool LinhaValor<T>::editavel() const
	//{
	//	return varAdjGen != nullptr;
	//}

	//template <typename T>
	//String LinhaValor<T>::texto(const bool imprimeValor) const
	//{
	//	auto txt = nome;
	//	for (auto i = 0; i < nAlgarismos; i++)
	//		txt += " ";
	//	if (nCaracteres() < 16)
	//		txt += " ";
	//	txt += unidade;
	//	if (!imprimeValor)
	//		return txt;
	//	auto valor = printValor();
	//	const auto index = nome.length();
	//	for (auto i = 0; i < valor.length() && index + i < 16; i++)
	//		txt.setCharAt(index + i, valor[i]); //*/
	//	return txt;
	//}

	//template <typename T>
	//String LinhaValor<T>::texto() const
	//{
	//	return texto(true);
	//}
}