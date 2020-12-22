// 
// 
// 

#include "MenuLinhas.h"


void MenuLinhas::resetaEnums()
{
	enums[EnumMain] = 0;
	editValorLinha = false;
}

void MenuLinhas::atualizaPisca()
{
	switch (indexEnum) 
	{
		case EnumMain:
		default:
			pisca.redefine(tAceso1, tApagado1, tLoop);
			break;
		case EnumIndexSup: 
		case EnumIndexInf:
			pisca.redefine(tAceso2, tApagado2, tLoop);
			break;
	}
}

String MenuLinhas::atualizaLinha(const bool linhaSup)
{
	const auto aceso = !pisca.aceso();
	if (linhaSup)
	{
		if (aceso || enums[EnumMain] != 1)
			return LinhaBase::textoCenter(linhas[enums[EnumIndexSup]].texto(true, true), offset);
		switch (indexEnum) 
		{
			case EnumMain:
				return LinhaBase::limpa();
			case EnumIndexSup:
				if(editValorLinha)
					return LinhaBase::textoCenter(linhas[enums[EnumIndexSup]].texto(true, false), offset);
				return LinhaBase::textoCenter(linhas[enums[EnumIndexSup]].texto(false, true), offset);
			default:
				return LinhaBase::textoCenter(linhas[enums[EnumIndexSup]].texto(true, true), offset);
		}
	}
	if (aceso || enums[EnumMain] != 2)
		return LinhaBase::textoCenter(linhas[enums[EnumIndexInf]].texto(true, true), offset);
	switch (indexEnum)
	{
		case EnumMain:
			return LinhaBase::limpa();
		case EnumIndexInf:
			if (editValorLinha)
				return LinhaBase::textoCenter(linhas[enums[EnumIndexInf]].texto(true, false), offset);
			return LinhaBase::textoCenter(linhas[enums[EnumIndexInf]].texto(false, true), offset);
		default:
			return LinhaBase::textoCenter(linhas[enums[EnumIndexInf]].texto(true, true), offset);
	}
}

void MenuLinhas::ini(EnumMenus* menuAtual, Logo* logo, LinhaValor<float> linhas[], const uint8_t nLinhas, void(*loopMenu)(),
								const uint8_t logoSize, const uint8_t offset, const uint16_t tLoop)
{
	this->menuIhm = menuAtual;
	this->logo = logo;
	this->linhas = linhas;
	this->nLinhas = nLinhas;
	this->loopMenu = loopMenu;
	this->logoSize = logoSize;
	this->offset = offset;
	this->tLoop = tLoop;
	pisca.redefine(tAceso1, tApagado1, tLoop);
	trocaEnum[EnumIndexSup].max = nLinhas - 1;
	trocaEnum[EnumIndexInf].max = nLinhas - 1;
}

void MenuLinhas::onMenuIni(void(* logoUpdate)(Logo logos))
{
	updateLogo = logoUpdate;
	atualizaLogo();
	resetaEnums();
}

void MenuLinhas::atualizaLogo() const
{
	if (updateLogo == nullptr)
		return;
	updateLogo(*logo);
}

void MenuLinhas::onLoop()
{
	atualizaPisca();
	linhaSuperior = atualizaLinha(true);
	linhaInferior = atualizaLinha(false);
	if (loopMenu != nullptr)
		loopMenu();
	//Serial.print(F("IndexEnum: "));
	//Serial.println(indexEnum);
	//Serial.print(F("enums[indexEnum]: "));
	//Serial.println(enums[indexEnum]);
	//Serial.print(F("editValorLinha: "));
	//Serial.println(editValorLinha);
}

void MenuLinhas::onEncdrDec()
{
	if (select)
		return;
	if (editValorLinha)
		linhas[enums[indexEnum]].varAdjGen->dec();
	else
		trocaEnum[indexEnum].dec();
}

void MenuLinhas::onEncdrInc()
{
	if (select)
		return;
	if (editValorLinha)
		linhas[enums[indexEnum]].varAdjGen->inc();
	else
		trocaEnum[indexEnum].inc();
}

void MenuLinhas::onClick()
{
	switch (indexEnum)
	{
		case EnumMain:
			switch (enums[EnumMain])
				{
				default:
					onEncdrInc();
					break;
				case 1:
					indexEnum = EnumIndexSup;
					break;
				case 2:
					indexEnum = EnumIndexInf;
					break;
				}
			editValorLinha = false;
		break;
		default:
		case EnumIndexSup:
		case EnumIndexInf:
			digitalWrite(12, false);// !digitalRead(12));
			if (editValorLinha)
			{
				indexEnum = EnumMain;
				editValorLinha = false;
			}
			else
				if (linhas[enums[indexEnum]].editavel())
					editValorLinha = true;
				else
					indexEnum = EnumMain;
			break;
	}
}

void MenuLinhas::onVoltar()
{
	switch (indexEnum)
	{
		case EnumMain:
			switch (enums[EnumMain])
			{
			default:
				*menuIhm = menuAnterior;
				break;
			case 1:
			case 2:
				enums[EnumMain] = 0;
				break;
			}
		case EnumIndexSup:
		case EnumIndexInf:
			if (editValorLinha)
				editValorLinha = false;
			else
				indexEnum = EnumMain;
			break;
	}
}

uint8_t* MenuLinhas::pntrLinhas()
{
	return &enums[EnumIndexSup];
}
