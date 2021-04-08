#include "MenuPortal.h"

void MenuPortal::atualizaLogo() const
{
	if (updateLogo == nullptr || portais[enumerador].logo.logoPtr == nullptr)
		return;
	updateLogo(portais[enumerador].logo);
}

MenuPortal::MenuPortal(const String& titulo, EnumMenus* menuAtual, const EnumMenus menuVoltar,
						const uint8_t nEnum, String nomeEnums[], const uint16_t tLoop) :
						tLoop(tLoop), pisca(tAceso, tApagado, tLoop)
{
	this->titulo = titulo;
	menuIhm = menuAtual;
	this->menuVoltar = menuVoltar;
	this->nEnum = nEnum;
	trocaEnum = { enumerador, 0, nEnum - 1, 1, true };
	portais = new Portal[nEnum];
	for (uint8_t i = 0; i < nEnum; i++)
		portais[i] = { nomeEnums[i], {nullptr, 0}, EnumMenus::Nada };
}

MenuPortal::MenuPortal(const String& titulo, EnumMenus* menuAtual, const EnumMenus menuVoltar,
						const uint8_t nEnum, Portal* portais, const uint8_t logoSize, const uint8_t offset,
						const uint16_t tLoop) : pisca(tAceso, tApagado, tLoop)
{
	ini(titulo, menuAtual, menuVoltar, nEnum, portais, logoSize, offset, tLoop);
}

void MenuPortal::ini(const String& titulo, EnumMenus* menuAtual, const EnumMenus menuVoltar, const uint8_t nEnum, Portal* portais,
                     const uint8_t logoSize, const uint8_t offset, const uint16_t tLoop)
{
	this->titulo = titulo;
	menuIhm = menuAtual;
	this->menuVoltar = menuVoltar;
	this->nEnum = nEnum;
	trocaEnum = { enumerador, 0, nEnum - 1, 1, true };
	this->portais = portais;
	this->logoSize = logoSize;
	this->offset = offset;
	this->tLoop = tLoop;
	pisca.redefine(tAceso, tApagado, tLoop);
}

void MenuPortal::onMenuIni(void (*logoUpdate)(Logo logos))
{
	updateLogo = logoUpdate;
	atualizaLogo();
}

void MenuPortal::onLoop()
{
	if (select)
	{
		select--;
		if (!select)
		{
			if(portais[enumerador].destino != Nada)
				*menuIhm = portais[enumerador].destino;
			pisca.redefine(tAceso, tApagado, tLoop);
		}
	}
	const auto imprime = pisca.aceso();
	linhaSuperior = MenuExtensoes::LinhaBase::textoCenter(titulo, offset);
	if (imprime)
		linhaInferior = MenuExtensoes::LinhaBase::textoCenter(portais[enumerador].nome, offset);
	else
		linhaInferior = MenuExtensoes::LinhaBase::limpa();
	if (enumerador != enumeradorAnt)
		atualizaLogo();
	enumeradorAnt = enumerador;
}

void MenuPortal::onEncdrDec(const int mult = 1)
{
	if (select)
		return;
	trocaEnum.dec();
	pisca.reseta();
}

void MenuPortal::onEncdrInc(const int mult = 1)
{
	if (select)
		return;
	trocaEnum.inc();
	pisca.reseta();
}

void MenuPortal::onClick()
{
	select = 1000 / tLoop;
	pisca.reseta(150, 150, tLoop);
}

void MenuPortal::onVoltar()
{
	*menuIhm = menuVoltar;
}
