// MenuLinhas.h

#ifndef _MENUEXECUCAO_h
#define _MENUEXECUCAO_h
#include <MenuBase.h>/*
#include "../Base/MenuBase.h"//*/

using namespace MenuExtensoes;


class MenuLinhas final : public MenuBase
{
    enum EstadoIndex
    {
        EnumMain = 0,
        EnumIndexSup,
        EnumIndexInf
    };

    //Enums
    uint8_t enums[3] = {0, 0, 1}; //valores do enum da ihm, enum da linha de cima, e enum da linha de baixo
    AdjGenerico<uint8_t> trocaEnum[3] = 
    { 
    	{ enums[EnumMain], 0, 2, 1, true }, 
    	{ enums[EnumIndexSup], 0, 1, 1, true }, 
    	{ enums[EnumIndexInf], 0, 1, 1, true }
    };
    EstadoIndex indexEnum = EnumMain;
    bool editValorLinha = false;
    volatile byte select = 0;
	//Pisca
    const uint16_t tAceso1 = 600, tApagado1 = 400,
					tAceso2 = 300, tApagado2 = 200;
    uint16_t tLoop = 50;
    PiscaCiclo pisca;
    void(*updateLogo)(const Logo& logo) = nullptr;
    uint8_t logoSize = 0;
    uint8_t offset = 0;
    //LINHAS
    LinhaValor<float>* linhas = nullptr;
    uint8_t nLinhas = 0;

    void resetaEnums();

    void atualizaPisca();

    String atualizaLinha(bool linhaSup);

public:
    MenuLinhas() = default;

    void(*loopMenu)() = nullptr;

    void ini(EnumMenus* menuAtual, const Logo& logo, LinhaValor<float> linhas[], uint8_t nLinhas, void(*loopMenu)(),
						uint8_t logoSize, uint8_t offset, uint16_t tLoop);

    void onMenuIni(void (*logoUpdate)(const Logo& logo)) override;

    //Logo
    const Logo* logo = nullptr;

    void atualizaLogo() override;

    void onLoop() override;

    void onEncdrDec(int mult) override;

    void onEncdrInc(int mult) override;

    void onClick() override;

    void onVoltar() override;

    uint8_t* pntrLinhas();
};

#endif

