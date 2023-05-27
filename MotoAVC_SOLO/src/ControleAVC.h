// ControleAVC.h

#ifndef _CONTROLEAVC_h
#define _CONTROLEAVC_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum StatusControle
{
    Off,
    Abrindo,
    Descendo,
    Subindo,
    Ok
};

class ControleAVC
{
    const int tensaoDoArco = A6;  // Entrada analogica, leitura da tensao do arco
    const int saidaComarc = 6;  // sinal enviado ao motoman
    const float ajuste5V = 5 / 1024.0;
    const float a = -1.003671372f, b = 0.990497072f;
    const float alpha = 0.01;
    const float tensaoSaidaMax = 8.8;
    uint8_t pinAbertura = 255;
    uint8_t pinArcoBom = 255;

    float leTensaoArco() const;
    void atualizaStatusControle(float leitura);
    StatusControle statusControle = Off;
    unsigned long instAbertura = 0;

 public:
    void setupControle() const;
    void setupControle(uint8_t pinArcoBom, uint8_t pinAbertura);

    float valorTensaoDoArco = 0;
    float mediaTensaoDoArco = 0;
    float valorSaida = 0;
    float valorSaidaCorrente = 0;

    float leituraEntradaAnalogica = 0;
    float multEntradaAnalogica = 1;
    float referencia = 12.6;
    float zonaMorta = 0;
    float erro = 0;
    float tDelay = 0; //segundos
    bool modoAuto = false;
    StatusControle getStatusControle() const;

    void setaSaida(float leitura);
    String imprime() const;
    void atua();
};

extern ControleAVC Controle;

#endif

