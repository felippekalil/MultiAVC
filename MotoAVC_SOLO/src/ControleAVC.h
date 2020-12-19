// ControleAVC.h

#ifndef _CONTROLEAVC_h
#define _CONTROLEAVC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ControleAVC
{
    const int tensaoDoArco = A6;  // Entrada analogica, leitura da tensao do arco
    const int saidaComarc = 6;  // sinal enviado ao motoman

    float leTensaoArco() const;

 public:
    void setupControle() const;

    float valorTensaoDoArco = 0;
    float valorSaida = 0;
    float valorSaidaCorrente = 0;

    float leituraEntradaAnalogica = 0;
    float referencia = 12.6;
    float zonaMorta = 1.1;

    void setaSaida(float leitura);

    String imprime() const;

    void atua();
};

extern ControleAVC Controle;

#endif

