// Menus.h

#ifndef _MENUS_h
#define _MENUS_h

#include "MenuBase.h"

struct Portal
{
    String nome;
    MenuBase::Logo logo;
    EnumMenus destino;
    //Portal() = default;
    //Portal(String& nome, const MenuBase::Logo logo, const EnumMenus::Menus destino) : nome(nome), logo(logo), destino(destino) {}
};

class MenuPortal final : public MenuBase
{
    String titulo;
    Portal* portais = nullptr;
    uint8_t nEnum;
    uint16_t enumerador = 0, enumeradorAnt = 0;
    MenuExtensoes::AdjGenerico<uint16_t> trocaEnum{};
    volatile byte select = 0;
    const uint16_t tAceso = 800, tApagado = 500, tLoop;
    MenuExtensoes::PiscaCiclo pisca;
    EnumMenus menuVoltar;

    void(*updateLogo)(Logo logo) = nullptr;

    uint8_t logoSize = 0;
    uint8_t offset = 0;

    void atualizaLogo() const;

public:
    MenuPortal(const String& titulo, EnumMenus* menuAtual, EnumMenus menuVoltar, uint8_t nEnum,
        String nomeEnums[], uint16_t tLoop);

    MenuPortal(const String& titulo, EnumMenus* menuAtual, EnumMenus menuVoltar, uint8_t nEnum,
        Portal* portais, uint8_t logoSize, uint8_t offset, uint16_t tLoop);

    void onMenuIni(void (*logoUpdate)(Logo logos)) override;

    void onLoop() override;

    void onEncdrDec() override;

    void onEncdrInc() override;

    void onClick() override;

    void onVoltar() override;
};

#endif

