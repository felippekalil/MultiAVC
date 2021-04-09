#pragma once
#include "MenuBase.h"

class MenuMensagem final : public MenuBase
{
    String textoSuperior, textoInferior;
    const uint16_t tAceso = 500, tApagado = 100;
    uint16_t tDuracao = 1400, contDuracao = 0;
    MenuExtensoes::PiscaCiclo pisca;

    void(*updateLogo)(const Logo& logo) = nullptr;
    Logo logo{nullptr, 0};
    uint8_t logoSize = 0;
    uint8_t offset = 0;
    void atualizaLogo() const;

public:
    MenuMensagem() = default;
    MenuMensagem(const String& textoSuperior, const String& textoInferior, EnumMenus* menuAtual,
                 const Logo& logo, uint8_t logoSize, uint8_t offset, uint16_t tLoop);

    void ini(const String& textoSuperior, const String& textoInferior, EnumMenus* menuAtual,
             const Logo& logo, uint8_t logoSize, uint8_t offset, uint16_t tLoop);

    void onMenuIni(void (*logoUpdate)(const Logo& logo)) override;

    void onLoop() override;

    void onVoltar() override;

    void onEncdrDec(int mult) override {}
    void onEncdrInc(int mult) override {}
    void onClick() override {}
};

