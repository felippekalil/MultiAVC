// MenuExecucao.h

#ifndef _MENUEXECUCAO_h
#define _MENUEXECUCAO_h
#include "../Base/MenuBase.h"


class MenuExecucao final : public MenuBase
{
    //Enums
    uint8_t nEnum;
    uint16_t enumerador = 0, enumeradorAnt = 0;
    MenuExtensoes::AdjGenerico<uint16_t> trocaEnum{};
    volatile byte select = 0;
	//Pisca
	const uint16_t tAceso = 800, tApagado = 500, tLoop;
    MenuExtensoes::PiscaCiclo pisca;
    //Logo
    void(*updateLogo)(Logo logo) = nullptr;
    uint8_t logoSize = 0;
    uint8_t offset = 0;

    void atualizaLogo() const;

public:
    MenuExecucao();

    void onMenuIni(void (*logoUpdate)(Logo logos)) override;

    void onLoop() override;

    void onEncdrDec() override;

    void onEncdrInc() override;

    void onClick() override;

    void onVoltar() override;
};

#endif

