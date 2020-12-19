/*
 Name:		MotoAVC_SOLO.ino
 Created:	11/26/2020 8:55:52 PM
 Author:	Kalil
*/

#define TLOOP 50 // ms

#include "EEPROM.h"
#include <LiquidCrystal.h>
#include "IHMv2.h"
#include "src/Menus.h"
#include "src/ControleAVC.h"

using namespace IHMv2;

Ihm ihm(TLOOP);

namespace Eeprom
{
    float refEeprom;

    void loadEeprom()
    {
        EEPROM.get(0, Controle.referencia);
        refEeprom = Controle.referencia;
    }

    void atualizaEeprom() // se não for lenta a leitura da eeprom, dá pra rodar o update diretamente, e deletar o refEeprom
    {
        if (refEeprom != Controle.referencia)
        {
            EEPROM.put(0, Controle.referencia);
            refEeprom = Controle.referencia;
            Serial.println("Referencia Atualizada!");
            Serial.println("Ref: " + String(Controle.referencia, 1) + " V");
        }
    }
}


void setup() {
    Serial.begin(9600);
    Serial.println("Inicializado!");
    Controle.setupControle();
    Menus.init(TLOOP);
    ihm.setup();
    ihm.atualizaMenu(Menus.menus[Menus.menuIhmIndex]);
    Eeprom::loadEeprom();
    Serial.println("Referencia Atualizada!");
    Serial.println("Ref: " + String(Controle.referencia, 1) + " V");
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
}
