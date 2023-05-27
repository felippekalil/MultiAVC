// 
// 
// 

#include "ControleAVC.h"

ControleAVC Controle;

float ControleAVC::leTensaoArco() const
{
	return static_cast<float>(multEntradaAnalogica * b * powf(1.0 / (static_cast<float>(analogRead(tensaoDoArco)) * ajuste5V), a));
}

void ControleAVC::atualizaStatusControle(const float leitura)
{
	if (leitura == referencia)
		statusControle = Ok;
	else if (leitura > referencia)
		statusControle = Descendo;
	else if (leitura < referencia)
		statusControle = Subindo;
}

void ControleAVC::setupControle() const
{
	pinMode(tensaoDoArco, INPUT);
	pinMode(saidaComarc, OUTPUT);
}

void ControleAVC::setupControle(const uint8_t pinArcoBom, const uint8_t pinAbertura = 255)
{
	this->pinArcoBom = pinArcoBom;
	this->pinAbertura = pinAbertura;
	pinMode(pinArcoBom, OUTPUT);
	if (pinAbertura != 255)
		pinMode(pinAbertura, OUTPUT);
	pinMode(tensaoDoArco, INPUT);
	pinMode(saidaComarc, OUTPUT);
}

StatusControle ControleAVC::getStatusControle() const
{
	return statusControle;
}

void ControleAVC::setaSaida(float leitura)
{
	if (leitura < referencia + zonaMorta && leitura > referencia - zonaMorta)
		leitura = referencia;

	atualizaStatusControle(leitura);

	valorSaida = (leitura * (-tensaoSaidaMax) / (2 * referencia) + tensaoSaidaMax);

	if (valorSaida < 0)
		valorSaida = 0;
	if (valorSaida > tensaoSaidaMax)
		valorSaida = tensaoSaidaMax;

	valorSaidaCorrente = valorSaida * 100 * 300 / 440.0f;
	analogWrite(saidaComarc, static_cast<int>(255 - 255 * (valorSaida) / tensaoSaidaMax));
}

String ControleAVC::imprime() const
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

void ControleAVC::atua()
{
	valorTensaoDoArco = leTensaoArco(); //Atuação
	mediaTensaoDoArco = valorTensaoDoArco * alpha + mediaTensaoDoArco * (1 - alpha); //Display e AutoRef
	erro = mediaTensaoDoArco - referencia; //Display
	if (mediaTensaoDoArco < referencia / 3.0 || mediaTensaoDoArco > 2 * referencia) //Região OFF
	{
		setaSaida(referencia); //não atua
		if (valorTensaoDoArco > 2 * referencia)
		{
			statusControle = Abrindo;
			instAbertura = millis();
		}
		else if (valorTensaoDoArco < referencia / 3.0)
			statusControle = Off;
	}
	else
	{
		if (!modoAuto)
			setaSaida(valorTensaoDoArco);//atua
		else 
		{//Atualiza Ref à todo início
			auto agora = millis();
			if (agora - instAbertura < tDelay * 1000) // se está esperando o tDelay
			{
				referencia = mediaTensaoDoArco; //Vai atualizando a referência
				setaSaida(referencia); // Não atua enquanto isso
			}
			else //se já deu o tempo
				setaSaida(valorTensaoDoArco);//atua
		}
	}

	if (pinAbertura != 255)
		digitalWrite(pinAbertura, statusControle == Abrindo);
	if (pinArcoBom != 255)
		digitalWrite(pinArcoBom, statusControle == Ok);
}


