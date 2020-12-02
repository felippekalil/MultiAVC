#pragma once
#include "MenuBase.h"

class MenuMensagem final : public MenuBase
{
    String textoSuperior, textoInferior;
    const uint16_t tAceso = 800, tApagado = 100, tLoop;
    MenuExtensoes::PiscaCiclo pisca;
    EnumMenus::Menus menuVoltar;

    void(*updateLogo)(Logo logo) = nullptr;
    Logo logo{};
    uint8_t logoSize = 0;
    uint8_t offset = 0;
    void atualizaLogo() const;

public:
    MenuMensagem(const String& textoSuperior, const String& textoInferior, EnumMenus::Menus* menuAtual, EnumMenus::Menus menuVoltar,
        Logo logo, uint8_t logoSize, uint8_t offset, uint16_t tLoop);

    void onMenuIni(void (*logoUpdate)(Logo logos)) override;

    void onLoop() override;

    void onVoltar() override;

    void onEncdrDec() override {}
    void onEncdrInc() override {}
    void onClick() override {}
};

