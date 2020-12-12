#include "MenuMensagem.h"

void MenuMensagem::atualizaLogo() const
{
	if (updateLogo == nullptr || logo.logoPtr == nullptr)
		return;
	updateLogo(logo);
}

MenuMensagem::MenuMensagem() = default;

MenuMensagem::MenuMensagem(const String& textoSuperior, const String& textoInferior, EnumMenus::Menus* menuAtual,
                           const Logo logo, const uint8_t logoSize, const uint8_t offset, const uint16_t tLoop) 
							: pisca(tAceso, tApagado, tLoop)
{
	ini(textoSuperior, textoInferior, menuAtual, logo, logoSize, offset, tLoop);
	//this->textoSuperior = textoSuperior;
	//this->textoInferior = textoInferior;
	//menuIhm = menuAtual;
	//this->logo = logo;
	//this->logoSize = logoSize;
	//this->offset = offset;
	//tDuracao = tDuracao / tLoop;
}

void MenuMensagem::ini(const String& textoSuperior, const String& textoInferior, EnumMenus::Menus* menuAtual, const Logo logo,
                       const uint8_t logoSize, const uint8_t offset, const uint16_t tLoop) 
{
	this->textoSuperior = textoSuperior;
	this->textoInferior = textoInferior;
	menuIhm = menuAtual;
	this->logo = logo;
	this->logoSize = logoSize;
	this->offset = offset;
	tDuracao = tDuracao / tLoop;
	pisca.redefine(tAceso, tApagado, tLoop);
}

void MenuMensagem::onMenuIni(void(*logoUpdate)(Logo logos))
{
	updateLogo = logoUpdate;
	atualizaLogo();
	contDuracao = 0;
}


void MenuMensagem::onLoop()
{
	const auto imprime = pisca.aceso();
	if (imprime)
	{
		linhaSuperior = MenuExtensoes::LinhaBase::textoCenter(textoSuperior, offset);
		linhaInferior = MenuExtensoes::LinhaBase::textoCenter(textoInferior, offset);
	}
	else
	{
		linhaSuperior = MenuExtensoes::LinhaBase::limpa();
		linhaInferior = MenuExtensoes::LinhaBase::limpa();
	}
	contDuracao++;
	if (contDuracao > tDuracao*0.3 && contDuracao < tDuracao*0.5) // segura um pouco
		apitar = 3;
	if (contDuracao > tDuracao)	
		onVoltar();
}

void MenuMensagem::onVoltar()
{
	*menuIhm = menuAnterior;
}