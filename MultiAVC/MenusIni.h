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
constexpr uint16_t tLoop = 200;

class MenuBase : public Menu
{
    String titulo;
    uint8_t nEnum;
    String* nomeModos;
    uint16_t enumerador = 0, enumeradorAnt = 0;
    AdjGenerico<uint16_t> trocaEnum{};
    volatile byte select = 0;
    const uint16_t tAceso = 800, tApagado = 500, tCiclo = tLoop;
    PiscaCiclo pisca;
    MenusEnum::Menus menuVoltar;

    void(*updateLogo)(uint8_t logo[][8], uint8_t offset) = nullptr; 
    byte(**logos)[8] = nullptr;

    uint8_t logoSize = 0;// = 3;
    uint8_t offset = 0;// = -(logoSize + 1);
    uint8_t offsetLogo = 0;// = 15 - logoSize - 1;//*/

    void atualizaLogo() const
    {
        if (updateLogo == nullptr || logos == nullptr)
            return;
        updateLogo(logos[enumerador], offsetLogo);
    }

public:
    MenuBase(const String& titulo, MenusEnum::Menus* menuAtual, const MenusEnum::Menus menuVoltar, const uint8_t nEnum, String nomeEnums[]) : pisca(tAceso, tApagado, tCiclo)
    {
        this->titulo = titulo;
        menuIhm = menuAtual;
        this->menuVoltar = menuVoltar;
        this->nEnum = nEnum;
        trocaEnum = { &enumerador, 0, nEnum - 1, 1 };
        nomeModos = nomeEnums;
        this->logoSize = logoSize;
        this->offset = offset;
        this->offsetLogo = offsetLogo;
    }

    MenuBase(const String& titulo, MenusEnum::Menus* menuAtual, const MenusEnum::Menus menuVoltar, const uint8_t nEnum, String nomeEnums[], byte(*logos[])[8], const uint8_t logoSize, const uint8_t offset, const uint8_t offsetLogo) : pisca(tAceso, tApagado, tCiclo)
    {
        this->titulo = titulo;
        menuIhm = menuAtual;
        this->menuVoltar = menuVoltar;
        this->nEnum = nEnum;
        trocaEnum = { &enumerador, 0, nEnum - 1, 1 };
        nomeModos = nomeEnums;
        this->logos = logos;
        this->logoSize = logoSize;
        this->offset = offset;
        this->offsetLogo = offsetLogo;
    }

    void onMenuIni(void(*logoUpdate)(uint8_t logo[][8], uint8_t offset)) override
    {
        updateLogo = logoUpdate;
        atualizaLogo();
    }

    void onLoop() override
    {
        if (select)
        {
            select--;
            if (!select)
            {
                *menuIhm = MenusEnum::Processos;
                pisca.redefine(tAceso, tApagado, tCiclo);
            }
        }
        const auto imprime = pisca.aceso();
        linhaSuperior = LinhaBase::textoCenter(titulo, offset);
        if (imprime)
            linhaInferior = LinhaBase::textoCenter(nomeModos[enumerador], offset);
        else
            linhaInferior = LinhaBase::limpa();
        if (enumerador != enumeradorAnt)
            atualizaLogo();
        enumeradorAnt = enumerador;
    }

    void onEncdrDec() override
    {
        if (select)
            return;
        trocaEnum.dec();
        pisca.reseta();
    }

    void onEncdrInc() override
    {
        if (select)
            return;
        if (enumerador == trocaEnum.max)
            enumerador = trocaEnum.min;
        else
            trocaEnum.inc();
        pisca.reseta();
    }

    void onClick() override
    {
        select = 1000 / tCiclo;
        pisca.reseta(150, 150, tCiclo);
    }

    void onVoltar() override
    {
        *menuIhm = menuVoltar;
    }
};

#endif

