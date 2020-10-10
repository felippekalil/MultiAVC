// MenusIni.h

#ifndef _MENUSINI_h
#define _MENUSINI_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Menu.h"
#include "IHMv2.h"
using namespace IHMv2;

class MenuBase : public Menu
{    
    String titulo;
    uint8_t nEnum;
    String* nomeModos;
    uint16_t enumerador = 0, enumeradorAnt = 0;
    MenuExtensoes::AdjGenerico<uint16_t> trocaEnum{};
    volatile byte select = 0;
    const uint16_t tAceso = 800, tApagado = 500, tLoop;
    MenuExtensoes::PiscaCiclo pisca;
    MenusEnum::Menus menuVoltar;

    void(*updateLogo)(Logo logo) = nullptr;
    Logo* logos = nullptr;

    uint8_t logoSize = 0;
    uint8_t offset = 0;

    void atualizaLogo() const;

public:
    MenuBase(const String& titulo, MenusEnum::Menus* menuAtual, const MenusEnum::Menus menuVoltar, const uint8_t nEnum,
             String nomeEnums[], const uint16_t tLoop);

    MenuBase(const String& titulo, MenusEnum::Menus* menuAtual, const MenusEnum::Menus menuVoltar, const uint8_t nEnum,
             String nomeEnums[], Logo* logos, const uint8_t logoSize, const uint8_t offset, const uint16_t tLoop);

    MenuBase(const String& titulo, MenusEnum::Menus* menuAtual, const MenusEnum::Menus menuVoltar, const uint8_t nEnum,
             String nomeEnums[], byte (*logos[])[8], const uint8_t logoSize, const uint8_t offset,
             const uint8_t offsetLogo, const uint16_t tLoop);

    void onMenuIni(void (*logoUpdate)(Logo logos)) override;

    void onLoop() override;

    void onEncdrDec() override;

    void onEncdrInc() override;

    void onClick() override;

    void onVoltar() override;
};

#endif

