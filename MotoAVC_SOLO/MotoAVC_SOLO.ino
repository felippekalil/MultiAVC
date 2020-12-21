/*
 Name:		MotoAVC_SOLO.ino
 Created:	11/26/2020 8:55:52 PM
 Author:	Kalil
*/

constexpr auto TLOOP = 50; // ms;
constexpr auto saidaLoop = 12;

#include "EEPROM.h"
#include <LiquidCrystal.h>
#include "IHMv2.h"
#include "src/Menus.h"
#include "src/ControleAVC.h"

using namespace IHMv2;

Ihm ihm(TLOOP);

namespace Eeprom
{
    constexpr uint8_t nVar = 2;
    float refEeprom[nVar];
    float* varEeprom[nVar];

    void inicializaVarsEeprom()
    {
        uint8_t i = 0;
        varEeprom[i++] = &Controle.referencia;
        varEeprom[i++] = &Controle.zonaMorta;
        //varEeprom[i++] = reinterpret_cast<float*>(Menus.linhasMenuExec());
    }

    void loadEeprom()
    {
        //return;
        for (auto i = 0; i < nVar; i++)
        {
            EEPROM.get(i * 4, *varEeprom[i]);
            refEeprom[i] = *varEeprom[i];
        }
    }

    void atualizaEeprom() // se não for lenta a leitura da eeprom, dá pra rodar o update diretamente, e deletar o refEeprom
    {
        //return;
        for (auto i = 0; i < nVar; i++)
        {
            if (refEeprom[i] != *varEeprom[i])
            {
                EEPROM.put(i * 4, *varEeprom[i]);
                refEeprom[i] = *varEeprom[i];
            //    Serial.println("VarEeprom Atualizada!");
            //    Serial.println("Var " + String(i) + ": " + String(*varEeprom[i]));
            }
        }
    }
}


void setup() {
    Serial.begin(115200);
    Serial.println(F("Inicializado!"));
    pinMode(saidaLoop, OUTPUT);
    Controle.setupControle();
    Menus.init(TLOOP);
    ihm.setup();
    ihm.atualizaMenu(Menus.menus[Menus.menuIhmIndex]);
    Eeprom::inicializaVarsEeprom();
    Eeprom::loadEeprom();
}

void loop() {
    Controle.atua();
    if (millis() % TLOOP == 0)
    {
        if (Menus.menuIhmIndex != Menus.menuIndexAnterior)
        {
            //Serial.println("MenuAnt = " + String(menuIndexAnterior));
            //Serial.println("MenuAtual = " + String(menuIhmIndex));
            Menus.menus[Menus.menuIhmIndex]->menuAnterior = Menus.menuIndexAnterior;
            ihm.atualizaMenu(Menus.menus[Menus.menuIhmIndex]);
        }
        if(Menus.menuIhmIndex != Nada)
            Menus.menuIndexAnterior = Menus.menuIhmIndex;
        ihm.loop();
    }
    if(ihm.varAjustadas())
	    Eeprom::atualizaEeprom();
    //digitalWrite(saidaLoop, !digitalRead(saidaLoop));
}
