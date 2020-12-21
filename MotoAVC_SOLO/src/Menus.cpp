// 
// 
// 
#include "Menus.h"
MenusClass* MenusClass::pntExterno;

void MenusClass::iniciaMenuProc()
{
    const auto logoSize = 3, offset = logoSize + 1, offsetLogo = 2;
    portaisProc[0] = { "TIG HF", {reinterpret_cast<uint8_t*>(&Icones::logoTig), offsetLogo, reinterpret_cast<uint8_t*>(&Icones::charRaio), 2}, Execucao };
    portaisProc[1] = { "TIG", {reinterpret_cast<uint8_t*>(&Icones::logoTig), offsetLogo}, Obras };
    portaisProc[2] = { " MIG Conv.", {reinterpret_cast<uint8_t*>(&Icones::logoMig), offsetLogo, reinterpret_cast<uint8_t*>(&Icones::charCurto), 2 }, Obras };
    portaisProc[3] = { " MIG Puls.", {reinterpret_cast<uint8_t*>(&Icones::logoMig), offsetLogo, reinterpret_cast<uint8_t*>(&Icones::charPulse), 2 }, Obras };
    menuProcessos.ini("Processo", &menuIhmIndex, Processos, 4, portaisProc, logoSize, offset, tLoop);
}

void MenusClass::iniciaMenuObras()
{
    const auto logoSize = 3, offset = logoSize + 0, offsetLogo = 2;
    logoObras = { reinterpret_cast<uint8_t*>(&Icones::logoMartelo), offsetLogo };
    menuEmObras.ini("EM", "OBRAS!", &menuIhmIndex, logoObras, logoSize, offset, tLoop);
}


void MenusClass::atualizaCharExec()
{
    //Serial.println("Status: " + String(Controle.getStatusControle()));
	switch (Controle.getStatusControle()) 
    { 
		case Off:
            logoExec.charExtra = reinterpret_cast<uint8_t*>(&Icones::charNone);
			break;
		case Abrindo: 
            logoExec.charExtra = reinterpret_cast<uint8_t*>(&Icones::charRaio);
            break;
		case Descendo:
            logoExec.charExtra = reinterpret_cast<uint8_t*>(&Icones::charDwn);
            break;
		case Subindo:
            logoExec.charExtra = reinterpret_cast<uint8_t*>(&Icones::charUp);
            break;
		case Ok:
            logoExec.charExtra = reinterpret_cast<uint8_t*>(&Icones::charOk);
            break;
		default: ;
	}
    menuExecucao.atualizaLogo();    
}

void MenusClass::iniciaMenuExec()
{
    AdjGenerico<float>  referencia = { &Controle.referencia, 0.1, 99.9, 0.1, false };
    AdjGenerico<float> zonaMorta = { &Controle.zonaMorta, 0, 99.9, 0.1, false };
    uint8_t i = 0;
    linhas[i++] = { "Ref: ", referencia, 1, 4, "V" };
    linhas[i++] = { " In: ", Controle.valorTensaoDoArco, 1, 4, "V" };
    linhas[i++] = { "Z.M: ", zonaMorta, 1, 4, "V" };
    linhas[i++] = { "Out: ", Controle.valorSaidaCorrente, 1, 4, "A" };
    linhas[i++] = { "Out: ", Controle.valorSaida, 1, 4, "V" };
    const auto logoSize = 3, offset = logoSize + 1, offsetLogo = 0;
    logoExec = { reinterpret_cast<uint8_t*>(&Icones::logoTig), offsetLogo, nullptr, 2 };
    pntExterno = this;
    menuExecucao.ini(&menuIhmIndex, &logoExec, linhas, nLinhasProc, []() { pntExterno->atualizaCharExec(); }, logoSize, offset, tLoop);
}

MenusClass::MenusClass()
{
     menus[Processos] = &menuProcessos;
     menus[Obras] = &menuEmObras;
     menus[Execucao] = &menuExecucao;
}

void MenusClass::init(int tLoop)
{
    iniciaMenuProc();
    iniciaMenuObras();
    iniciaMenuExec();
}

int* MenusClass::linhasMenuExec()
{
	return menuExecucao.pntrLinhas();
}


MenusClass Menus;

