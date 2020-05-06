#pragma once

namespace Controle
{
    const int tensaoDoArco = A6;  // Entrada analogica, leitura da tensao do arco
    const int saidaComarc = 6;  // sinal enviado ao motoman

    float valorTensaoDoArco = 0;
    float valorSaida = 0;

    float leituraEntradaAnalogica = 0;
    float referencia = 11;

    inline void setupControle()
    {
        pinMode(tensaoDoArco, INPUT);
        pinMode(saidaComarc, OUTPUT);
    }

    inline double leTensaoArco()
    {
        return (500.0) * (analogRead(tensaoDoArco)) / (11264.0);
    }

    inline void setaSaida(const double leitura)
    {
        valorSaida = leitura * (-5) / (2 * referencia) + 5;

        if(valorSaida < 0)
            valorSaida = 0;
        if(valorSaida > 5)
            valorSaida = 5;

        analogWrite(saidaComarc, 255 * (valorSaida) / 5);
    }

    inline String imprime()
    {
        auto texto = static_cast<String>(millis() / 1000.0);
        texto += "\t";
        texto += valorTensaoDoArco;
        texto += "\t";
        texto += 500.0 * leituraEntradaAnalogica / 11264.0;
        texto += "\t";
        texto += valorSaida;
        return texto;
    }

    inline void atua()
    {
        valorTensaoDoArco = leTensaoArco();
        if(valorTensaoDoArco < 3 || valorTensaoDoArco > 30)
            setaSaida(referencia);
          //  valorTensaoDoArco = referencia;
        else
            setaSaida(valorTensaoDoArco);
    }
}
