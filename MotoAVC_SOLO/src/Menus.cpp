// 
// 
// 
#include "Menus.h"
#include "ControleAVC.h"
MenusClass* MenusClass::pntrEstatico;

void MenusClass::iniciaMenuProc()
{
    static Portal portaisProc[CountMenus];
    const auto logoSize = 3, offset = logoSize + 1, offsetLogo = 2;
    auto i = 0;
    portaisProc[i++] = { "TIG HF", {reinterpret_cast<const uint8_t*>(&Icones::LOGO_TIG), offsetLogo, reinterpret_cast<const uint8_t*>(&Icones::CHAR_RAIO), 2}, Tig };
    portaisProc[i++] = { "TIG", {reinterpret_cast<const uint8_t*>(&Icones::LOGO_TIG), offsetLogo}, Tig };
    portaisProc[i++] = { " MIG Conv.", {reinterpret_cast<const uint8_t*>(&Icones::LOGO_MIG), offsetLogo, reinterpret_cast<const uint8_t*>(&Icones::CHAR_CURTO), 2 }, Obras };
    portaisProc[i++] = { " MIG Puls.", {reinterpret_cast<const uint8_t*>(&Icones::LOGO_MIG), offsetLogo, reinterpret_cast<const uint8_t*>(&Icones::CHAR_PULSE), 2 }, Mig };
    portaisProc[i++] = { " MIG Puls. AUTO", {reinterpret_cast<const uint8_t*>(&Icones::LOGO_MIG), offsetLogo, reinterpret_cast<const uint8_t*>(&Icones::CHAR_PULSE), 2 }, Mig };
    portaisProc[i++] = { "Config", {reinterpret_cast<const uint8_t*>(&Icones::LOGO_CONFIG), offsetLogo}, Config };
    menuProcessos.ini("Processo", &menuIhmIndex, Processos, i, portaisProc, logoSize, offset, tLoop);
}

void MenusClass::iniciaMenuObras()
{
    const auto logoSize = 3, offset = logoSize + 0, offsetLogo = 2;
    static Logo logoObras = { reinterpret_cast<const uint8_t*>(&Icones::LOGO_MARTELO), offsetLogo };
    menuEmObras.ini("EM", "OBRAS!", &menuIhmIndex, logoObras, logoSize, offset, tLoop);
}


void MenusClass::atualizaCharExec(Logo &logo)
{
    static uint16_t pisca = 0;
    pisca++;
    if (pisca == tPisca * 2)
        pisca = 0;
    if (pisca > tPisca * 1.5)
        logo.charExtra = nullptr; //desaparece
    else switch (Controle.getStatusControle()) 
    { 
		case Off:
            logo.charExtra = reinterpret_cast<const uint8_t*>(&Icones::CHAR_NONE);
			break;
		case Abrindo: 
            logo.charExtra = reinterpret_cast<const uint8_t*>(&Icones::CHAR_RAIO);
            break;
		case Descendo:
            logo.charExtra = reinterpret_cast<const uint8_t*>(&Icones::CHAR_DWN);
            break;
		case Subindo:
            logo.charExtra = reinterpret_cast<const uint8_t*>(&Icones::CHAR_UP);
            break;
		case Ok:
            logo.charExtra = reinterpret_cast<const uint8_t*>(&Icones::CHAR_OK);
            break;
		default: ;
	}  
}

void MenusClass::iniciaLinhasExec()
{
    static AdjGenerico<float>  referencia = { Controle.referencia, 0.1, 99.9, 0.1, false };
    referencia.atualiza();
    static AdjGenerico<float> zonaMorta = { Controle.zonaMorta, 0, 99.9, 0.1, false };
    zonaMorta.atualiza();
    uint8_t i = 0;
    linhasExec[i++] = { " In: ", Controle.mediaTensaoDoArco, 1, 4, "V" };
    linhasExec[i++] = { "Ref: ", referencia, 1, 4, "V" };
    linhasExec[i++] = { " +-: ", zonaMorta, 1, 4, "V" };
    linhasExec[i++] = { "Err:", Controle.erro, 1, 5, "V" };
}

void MenusClass::iniciaLinhasExecAuto()
{
    static AdjGenerico<float>  referencia = { Controle.referencia, 0.1, 99.9, 0.1, false };
    referencia.atualiza();
    static AdjGenerico<float> zonaMorta = { Controle.zonaMorta, 0, 99.9, 0.1, false };
    zonaMorta.atualiza();
    static AdjGenerico<float> tDelay = { Controle.tDelay, 0, 99.9, 0.1, false };
    tDelay.atualiza();
    uint8_t i = 0;
    linhasExecAuto[i++] = { " In: ", Controle.mediaTensaoDoArco, 1, 4, "V" };
    linhasExecAuto[i++] = { "  T: ", tDelay, 1, 4, "s" };
    linhasExecAuto[i++] = { " +-: ", zonaMorta, 1, 4, "V" };
    linhasExecAuto[i++] = { "Ref: ", referencia, 1, 4, "V" };
    linhasExecAuto[i++] = { "Err:", Controle.erro, 1, 5, "V" };
}

void MenusClass::iniciaMenuExecTig()
{
    const auto logoSize = 3, offset = logoSize + 1, offsetLogo = 0;
    const auto sizeExec = sizeof(linhasExec) / sizeof(linhasExec[0]);
    logoExecTig = { reinterpret_cast<const uint8_t*>(&Icones::LOGO_TIG), offsetLogo, nullptr, 2 };
    pntrEstatico = this;
    menuExecucaoTig.ini(&menuIhmIndex, logoExecTig, linhasExec, sizeExec, []() { pntrEstatico->atualizaCharExec(pntrEstatico->logoExecTig);  pntrEstatico->menuExecucaoTig.atualizaLogo();   }, logoSize, offset, tLoop);
}

void MenusClass::iniciaMenuExecMig()
{
    const auto logoSize = 3, offset = logoSize + 1, offsetLogo = 0;
    const auto sizeExec = sizeof(linhasExec) / sizeof(linhasExec[0]);
    logoExecMig = { reinterpret_cast<const uint8_t*>(&Icones::LOGO_MIG), offsetLogo, nullptr, 2 };
    logoExecMigAuto = { reinterpret_cast<const uint8_t*>(&Icones::LOGO_MIG_AUTO), offsetLogo, nullptr, 2 };
    menuExecucaoMig.ini(&menuIhmIndex, logoExecMig, linhasExec, sizeExec, []() { pntrEstatico->atualizaCharExec(pntrEstatico->logoExecMig);  pntrEstatico->menuExecucaoMig.atualizaLogo(); }, logoSize, offset, tLoop);
    menuExecucaoMigAuto.ini(&menuIhmIndex, logoExecMigAuto, linhasExec, sizeExec, []() { pntrEstatico->atualizaCharExec(pntrEstatico->logoExecMig);  pntrEstatico->menuExecucaoMigAuto.atualizaLogo(); }, logoSize, offset, tLoop);
}

void MenusClass::iniciaMenuConfig()
{
    static Logo logoConfig{};
    static LinhaValor<float> linhasConfig[4];
    static AdjGenerico<float> multEntrada = { Controle.multEntradaAnalogica, 1, 99.9, 0.1, false };
    multEntrada.atualiza();

    uint8_t i = 0;
    linhasConfig[i++] = { "Mlt: ", multEntrada, 1, 4, "x" };
    linhasConfig[i++] = { "Out: ", Controle.valorSaidaCorrente, 1, 4, "A" };
    linhasConfig[i++] = { " In: ", Controle.mediaTensaoDoArco, 1, 4, "V" };
    linhasConfig[i++] = { "Out: ", Controle.valorSaida, 1, 4, "V" };
    const auto logoSize = 3, offset = logoSize + 1, offsetLogo = 0;
    logoConfig = { reinterpret_cast<const uint8_t*>(&Icones::LOGO_CONFIG), offsetLogo, nullptr, 2 };
    menuConfig.ini(&menuIhmIndex, logoConfig, linhasConfig, i, []() {}, logoSize, offset, tLoop);
}//*/

MenusClass::MenusClass()
{
     menus[Processos] = &menuProcessos;
     menus[Obras] = &menuEmObras;
     menus[Tig] = &menuExecucaoTig;
     menus[Mig] = &menuExecucaoMig;
     menus[MigAuto] = &menuExecucaoMigAuto;
     menus[Config] = &menuConfig;
}

void MenusClass::init(const int tLoop)
{
    tPisca /= tLoop;
    this->tLoop = tLoop;
    iniciaLinhasExec();
    iniciaLinhasExecAuto();
    iniciaMenuProc();
    iniciaMenuObras();
    iniciaMenuExecTig();
    iniciaMenuExecMig();
    iniciaMenuConfig();
}

uint8_t* MenusClass::linhasMenuExec()
{
	return menuExecucaoTig.pntrLinhas();
}


MenusClass Menus;

