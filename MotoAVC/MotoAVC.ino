/*
 Name:		MotoAVC.ino
 Created:	5/3/2020 5:53:23 PM
 Author:	Kalil
*/

#include "Controle.h"
//#include "Interface.h"/*
#include "IHMv1.h"
using namespace IHMv1;

VarFloat referencia = { &Controle::referencia , 0.1, 99.9, 0.1 };
Ihm ihm(&referencia, &Controle::valorTensaoDoArco);//*/


void setup() {
    Serial.begin(9600);
    Serial.println("Inicializado!");
    Controle::setupControle();
   // Interface::setupInterface(&Controle::referencia, &Controle::valorTensaoDoArco);    /*
    ihm.setup();//*/
}

void loop() {
    Controle::atua();
    ihm.debounce(10);
	if(millis() % 200 == 0)
        //Interface::imprimeInterface();/*
        ihm.imprimeInterface();//*/
}
