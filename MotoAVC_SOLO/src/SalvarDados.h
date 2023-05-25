// SalvarDados.h

#ifndef _SALVARDADOS_h
#define _SALVARDADOS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "EEPROM.h"
#include "ControleAVC.h"

namespace Eeprom //TODO Criar a classe SalvarDados
{
    constexpr uint8_t nVar = 3;
    struct DadoEeprom // para valores de até 4 bytes
    {
        uint8_t* local{};
        uint8_t size{};
        uint32_t valor = 0;
        void ini(void* lcl, const uint8_t sz)
        {
            local = static_cast<uint8_t*>(lcl);
            size = sz;
            updateValor();
        }
        void updateValor()
        {
            memcpy(&valor, local, size);
        }
        bool atualizou() const
        {
            uint32_t valorAtual = 0;
            memcpy(&valorAtual, local, size);
            return valorAtual != valor;
        }
    };
    DadoEeprom refEeprom[nVar];

    void inicializaVarsEeprom()
    {
        uint8_t i = 0;
        refEeprom[i++].ini(&Controle.referencia, sizeof(Controle.referencia));
        refEeprom[i++].ini(&Controle.zonaMorta, sizeof(Controle.zonaMorta));
        refEeprom[i++].ini(&Controle.multEntradaAnalogica, sizeof(Controle.multEntradaAnalogica));
        refEeprom[i++].ini(&Controle.tDelay, sizeof(Controle.tDelay));
    }

    void printRef()
    {
        for (uint8_t i = 0; i < nVar; i++)
        {
            Serial.print(F("ref: "));
            Serial.print(i);
            Serial.print(F(" "));
            for (uint8_t j = 0; j < refEeprom[i].size; j++)
            {
                Serial.println(refEeprom[i].valor);
                Serial.print(F(" "));
            }
        }
    }

    void printEeprom()
    {
        for (uint8_t i = 0; i < nVar; i++)
        {
            float impr = 0;
            EEPROM.get(i * 4, impr);
            Serial.print(F("eep "));
            Serial.print(i);
            Serial.print(F(": "));
            Serial.println(impr);
        }
    }

    void carregaEeprom()
    {
        auto localEeprom = 0;
        for (auto& i : refEeprom)
            for (uint8_t j = 0; j < i.size; j++)
                *(i.local + j) = EEPROM.read(localEeprom++);
    }

    void atualizaEeprom()
    {
        for (uint8_t i = 0; i < nVar; i++)
            if (refEeprom[i].atualizou())
            {
                uint8_t localEeprom = 0;
                for (uint8_t j = 0; j < i; j++)
                    localEeprom += refEeprom[i].size;
                refEeprom[i].updateValor();
                for (uint8_t j = 0; j < refEeprom[i].size; j++)
                    EEPROM.write(localEeprom++, *(refEeprom[i].local + j));
            }
    }
}


#endif

