#include "MenusIni.h"

void MenuBase::atualizaLogo() const
{
	if (updateLogo == nullptr || logos == nullptr)
		return;
	updateLogo(logos[enumerador]);
}

MenuBase::MenuBase(const String& titulo, MenusEnum::Menus* menuAtual, const MenusEnum::Menus menuVoltar,
                   const uint8_t nEnum, String nomeEnums[], const uint16_t tLoop):
	tLoop(tLoop), pisca(tAceso, tApagado, tLoop)
{
	this->titulo = titulo;
	menuIhm = menuAtual;
	this->menuVoltar = menuVoltar;
	this->nEnum = nEnum;
	trocaEnum = {&enumerador, 0, nEnum - 1, 1};
	nomeModos = nomeEnums;
}

MenuBase::MenuBase(const String& titulo, MenusEnum::Menus* menuAtual, const MenusEnum::Menus menuVoltar,
                   const uint8_t nEnum, String nomeEnums[], Logo* logos, const uint8_t logoSize, const uint8_t offset,
                   const uint16_t tLoop):
	tLoop(tLoop), pisca(tAceso, tApagado, tLoop)
{
	this->titulo = titulo;
	menuIhm = menuAtual;
	this->menuVoltar = menuVoltar;
	this->nEnum = nEnum;
	trocaEnum = {&enumerador, 0, nEnum - 1, 1};
	nomeModos = nomeEnums;
	this->logos = logos;
	this->logoSize = logoSize;
	this->offset = offset;
}

MenuBase::MenuBase(const String& titulo, MenusEnum::Menus* menuAtual, const MenusEnum::Menus menuVoltar,
                   const uint8_t nEnum, String nomeEnums[], byte (* logos[])[8], const uint8_t logoSize,
                   const uint8_t offset,
                   const uint8_t offsetLogo, const uint16_t tLoop):
	tLoop(tLoop), pisca(tAceso, tApagado, tLoop)
{
	this->titulo = titulo;
	menuIhm = menuAtual;
	this->menuVoltar = menuVoltar;
	this->nEnum = nEnum;
	trocaEnum = {&enumerador, 0, nEnum - 1, 1};
	nomeModos = nomeEnums;
	const auto logosLogo = new Logo[nEnum];
	for (uint8_t i = 0; i < nEnum; i++)
		logosLogo[i] = {logos[i], offsetLogo};
	this->logos = logosLogo;
	this->logoSize = logoSize;
	this->offset = offset;
}

void MenuBase::onMenuIni(void (* logoUpdate)(Logo logos))
{
	updateLogo = logoUpdate;
	atualizaLogo();
}

void MenuBase::onLoop()
{
	if (select)
	{
		select--;
		if (!select)
		{
			*menuIhm = MenusEnum::Processos;
			pisca.redefine(tAceso, tApagado, tLoop);
		}
	}
	const auto imprime = pisca.aceso();
	linhaSuperior = MenuExtensoes::LinhaBase::textoCenter(titulo, offset);
	if (imprime)
		linhaInferior = MenuExtensoes::LinhaBase::textoCenter(nomeModos[enumerador], offset);
	else
		linhaInferior = MenuExtensoes::LinhaBase::limpa();
	if (enumerador != enumeradorAnt)
		atualizaLogo();
	enumeradorAnt = enumerador;
}

void MenuBase::onEncdrDec()
{
	if (select)
		return;
	trocaEnum.dec();
	pisca.reseta();
}

void MenuBase::onEncdrInc()
{
	if (select)
		return;
	if (enumerador == trocaEnum.max)
		enumerador = trocaEnum.min;
	else
		trocaEnum.inc();
	pisca.reseta();
}

void MenuBase::onClick()
{
	select = 1000 / tLoop;
	pisca.reseta(150, 150, tLoop);
}

void MenuBase::onVoltar()
{
	*menuIhm = menuVoltar;
}
