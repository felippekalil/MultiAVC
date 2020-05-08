/*
 Name:		MotoAVC.ino
 Created:	5/3/2020 5:53:23 PM
 Author:	Kalil
*/
#include "EEPROM.h"
#include "Controle.h"
//#include "Interface.h"/*
#include "IHMv1.h"
using namespace IHMv1;

Linha linhas[] = { Linha("   In:", &Controle::valorTensaoDoArco, 1, 5, "V"),
                   Linha("  Out:", &Controle::valorSaida, 1, 5, "V"),
				   Linha("  Out:", &Controle::valorSaidaCorrente, 0, 5, "A") };

VarFloat referencia = { &Controle::referencia , 0.1, 99.9, 0.1 };
//Ihm ihm(&referencia, &Controle::valorTensaoDoArco);/*
Ihm ihm(&referencia, linhas, 3);//*/
float refEeprom = 0;


void setup() {
    Serial.begin(9600);
    Serial.println("Inicializado!");
    Controle::setupControle();
   // Interface::setupInterface(&Controle::referencia, &Controle::valorTensaoDoArco);    /*
    ihm.setup();//*/
    EEPROM.get(0, Controle::referencia);
    refEeprom = Controle::referencia;
    Serial.println("Referencia Atualizada!");
    Serial.println("Ref: " + String(Controle::referencia, 1) + " V");
}

void atualizaEeprom() // se não for lenta a leitura da eeprom, dá pra rodar o update diretamente, e deletar o refEeprom
{
    if(refEeprom != Controle::referencia)
    {
        EEPROM.put(0, Controle::referencia);
        refEeprom = Controle::referencia;
        Serial.println("Referencia Atualizada!");
        Serial.println("Ref: " + String(Controle::referencia, 1) + " V");
    }
}

void loop() {
    Controle::atua();
	if(millis() % 300 == 0)
        //Interface::imprimeInterface();/*
        ihm.imprimeInterface();//*/
    if(ihm.varAjustadas())
        atualizaEeprom();
}
