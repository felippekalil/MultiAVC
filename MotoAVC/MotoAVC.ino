/*
 Name:		MotoAVC.ino
 Created:	5/3/2020 5:53:23 PM
 Author:	Kalil
*/
#include "EEPROM.h"
#include "Controle.h"
#include "IHMv1.h"
using namespace IHMv2;

AdjFloat referencia = { &Controle::referencia , 0.1, 99.9, 0.1 };
Linha linhas[] = {  Linha("  Ref:", &referencia, 1, 5, "V"), // 0
                    Linha("   In:", &Controle::valorTensaoDoArco, 1, 5, "V"), // 1
                    Linha("  Out:", &Controle::valorSaida, 1, 5, "V"), // 2
                    Linha("  Out:", &Controle::valorSaidaCorrente, 0, 5, "A"), // 3
                    Linha("    Leitura"), // 4
                    Linha("    Serial"), // 5
                    Linha("  Serial+CRC"), // 6
					Linha("   Analogica") }; // 7

//Ihm(Linha* linhas, byte (*seqTelas)[2], int nLinhas);
constexpr byte nTelas = 7;
byte telas[nTelas][2] = { {0,0},{ 0,1 },{0,2},{0,3},{4,5},{4,6},{4,7} };
Ihm ihm(linhas, telas, nTelas);
float refEeprom = 0;


void setup() {
    Serial.begin(9600);
    Serial.println("Inicializado!");
    Controle::setupControle();
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
        ihm.imprimeInterface();
    if(ihm.varAjustadas())
        atualizaEeprom();
}
