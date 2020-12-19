// Menus.h

#ifndef _MENUPORTAL_h
#define _MENUPORTAL_h

#include "MenuBase.h"

class Portal
{
public:
    String nome = "               ";
    MenuBase::Logo logo{};
    EnumMenus destino = Processos;

    Portal() = default;

    Portal(const String& nm, const MenuBase::Logo lg, const EnumMenus dest)
    {
        nome = nm;
        logo = lg;
        destino = dest;
    }

    Portal& operator = (const Portal& var)
    {
        this->nome = var.nome;
        this->logo = var.logo;
        this->destino = var.destino;
        return *this;
    }
};

class MenuPortal final : public MenuBase
{
    String titulo = "";
    Portal* portais = nullptr;
    uint8_t nEnum;
    uint16_t enumerador = 0, enumeradorAnt = 0;
    MenuExtensoes::AdjGenerico<uint16_t> trocaEnum{};
    volatile byte select = 0;
    const uint16_t tAceso = 800, tApagado = 500;
	uint16_t tLoop = 50;
    MenuExtensoes::PiscaCiclo pisca;
    EnumMenus menuVoltar;

    void(*updateLogo)(Logo logo) = nullptr;

    uint8_t logoSize = 0;
    uint8_t offset = 0;

    void atualizaLogo() const;

public:
    MenuPortal() = default;
    MenuPortal(const String& titulo, EnumMenus* menuAtual, EnumMenus menuVoltar, uint8_t nEnum,
        String nomeEnums[], uint16_t tLoop);

    MenuPortal(const String& titulo, EnumMenus* menuAtual, EnumMenus menuVoltar, uint8_t nEnum,
        Portal* portais, uint8_t logoSize, uint8_t offset, uint16_t tLoop);

    void ini(const String& titulo, EnumMenus* menuAtual, EnumMenus menuVoltar, uint8_t nEnum,
        Portal* portais, uint8_t logoSize, uint8_t offset, uint16_t tLoop);

    void onMenuIni(void (*logoUpdate)(Logo logos)) override;

    void onLoop() override;

    void onEncdrDec() override;

    void onEncdrInc() override;

    void onClick() override;

    void onVoltar() override;
};

#endif

