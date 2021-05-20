// 
// 
// 
#include "Menus.h"
#include "ControleAVC.h"
MenusClass* MenusClass::pntrEstatico;

void MenusClass::iniciaMenuProc()
{
    const auto logoSize = 3, offset = logoSize + 1, offsetLogo = 2;
    auto i = 0;
    portaisProc[i++] = { "TIG HF", {reinterpret_cast<const uint8_t*>(&Icones::logoTig), offsetLogo, reinterpret_cast<const uint8_t*>(&Icones::charRaio), 2}, Execucao };
    portaisProc[i++] = { "TIG", {reinterpret_cast<const uint8_t*>(&Icones::logoTig), offsetLogo}, Execucao };
  //  portaisProc[i++] = { " MIG Conv.", {reinterpret_cast<const uint8_t*>(&Icones::logoMig), offsetLogo, reinterpret_cast<const uint8_t*>(&Icones::charCurto), 2 }, Obras };
 //   portaisProc[i++] = { " MIG Puls.", {reinterpret_cast<const uint8_t*>(&Icones::logoMig), offsetLogo, reinterpret_cast<uint8_t*>(&Icones::charPulse), 2 }, Obras };
    portaisProc[i++] = { "CONFIG", {reinterpret_cast<const uint8_t*>(&Icones::logoConfig), offsetLogo}, Config };
    menuProcessos.ini("Processo", &menuIhmIndex, Processos, i, portaisProc, logoSize, offset, tLoop);
}

void MenusClass::iniciaMenuObras()
{
    const auto logoSize = 3, offset = logoSize + 0, offsetLogo = 2;
    logoObras = { reinterpret_cast<const uint8_t*>(&Icones::logoMartelo), offsetLogo };
    menuEmObras.ini("EM", "OBRAS!", &menuIhmIndex, logoObras, logoSize, offset, tLoop);
}


void MenusClass::atualizaCharExec()
{
    pisca++;
    if (pisca == tPisca * 2)
        pisca = 0;
    if (pisca > tPisca * 1.5)
        logoExec.charExtra = nullptr; //desaparece
       // logoExec.charExtra += 1; //movimenta
    else switch (Controle.getStatusControle()) 
    { 
		case Off:
            logoExec.charExtra = reinterpret_cast<const uint8_t*>(&Icones::charNone);
			break;
		case Abrindo: 
            logoExec.charExtra = reinterpret_cast<const uint8_t*>(&Icones::charRaio);
            break;
		case Descendo:
            logoExec.charExtra = reinterpret_cast<const uint8_t*>(&Icones::charDwn);
            break;
		case Subindo:
            logoExec.charExtra = reinterpret_cast<const uint8_t*>(&Icones::charUp);
            break;
		case Ok:
            logoExec.charExtra = reinterpret_cast<const uint8_t*>(&Icones::charOk);
            break;
		default: ;
	}
    menuExecucao.atualizaLogo();    
}

void MenusClass::iniciaMenuExec()
{
    AdjGenerico<float>  referencia = { Controle.referencia, 0.1, 99.9, 0.1, false };
    referencia.atualiza();
    AdjGenerico<float> zonaMorta = { Controle.zonaMorta, 0, 99.9, 0.1, false };
    zonaMorta.atualiza();

    uint8_t i = 0;
    linhasExec[i++] = { "Ref: ", referencia, 1, 4, "V" };
    linhasExec[i++] = { " In: ", Controle.mediaTensaoDoArco, 1, 4, "V" };
    linhasExec[i++] = { "Err:", Controle.erro, 1, 5, "V" };
    linhasExec[i++] = { " +-: ", zonaMorta, 1, 4, "V" };//*/
    const auto logoSize = 3, offset = logoSize + 1, offsetLogo = 0;
    logoExec = { reinterpret_cast<const uint8_t*>(&Icones::logoTig), offsetLogo, nullptr, 2 };
    pntrEstatico = this;
    menuExecucao.ini(&menuIhmIndex, logoExec, linhasExec, i, []() { pntrEstatico->atualizaCharExec(); }, logoSize, offset, tLoop);
}


void MenusClass::iniciaMenuConfig()
{
    AdjGenerico<float> multEntrada = { Controle.multEntradaAnalogica, 1, 99.9, 0.1, false };
    multEntrada.atualiza();

    uint8_t i = 0;
    linhasConfig[i++] = { "Mlt: ", multEntrada, 1, 4, "x" };
    linhasConfig[i++] = { " In: ", Controle.mediaTensaoDoArco, 1, 4, "V" };
    linhasConfig[i++] = { "Out: ", Controle.valorSaidaCorrente, 1, 4, "A" };
    linhasConfig[i++] = { "Out: ", Controle.valorSaida, 1, 4, "V" };
    const auto logoSize = 3, offset = logoSize + 1, offsetLogo = 0;
    logoConfig = { reinterpret_cast<const uint8_t*>(&Icones::logoConfig), offsetLogo, nullptr, 2 };
    pntrEstatico = this;
    menuConfig.ini(&menuIhmIndex, logoConfig, linhasConfig, i, []() {}, logoSize, offset, tLoop);
}//*/

MenusClass::MenusClass()
{
     menus[Processos] = &menuProcessos;
     menus[Obras] = &menuEmObras;
     menus[Execucao] = &menuExecucao;
     menus[Config] = &menuConfig;
}

void MenusClass::init(const int tLoop)
{
    tPisca /= tLoop;
    this->tLoop = tLoop;
    iniciaMenuProc();
    iniciaMenuObras();
    iniciaMenuExec();
    iniciaMenuConfig();
}

uint8_t* MenusClass::linhasMenuExec()
{
	return menuExecucao.pntrLinhas();
}


MenusClass Menus;

