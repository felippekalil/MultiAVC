// 
// 
// 

#include "MenusIni.h"
//
//
//namespace MenuPrincipal
//{
//    Menu menuPrincipal;
//    uint16_t modoOper;
//    AdjGenerico<uint16_t> trocaModoOper = { &modoOper, 0, 3, 1 };
//    String nomeModos[4] = { "    MOTOMAN     ","    TIG HF      ", "      TIG       ", "      MIG       " };
//
//    volatile byte select;
//    int pisca;
//
//    void menuPrincipalOnLoop()
//    {
//        //"0123456789012345"
//        menuPrincipal.linhaSuperior = "MODO DE OPERACAO";
//        menuPrincipal.linhaInferior = nomeModos[modoOper];
//    }
//
//    void menuPrincipalOnEncdrDec()
//    {
//        trocaModoOper.dec();
//    }
//
//    void menuPrincipalOnEncdrInc()
//    {
//        trocaModoOper.inc();
//    }
//
//    inline void menuPrincipalOnClick()
//    {
//        if(select > 1)
//            select = 0;
//        else
//            select++;
//    }
//
//    inline void menuPrincipalOnVoltar()
//    {
//        if(select < 1)
//            select = 2;
//        else
//            select--;
//    }
//
//    void inicializaMenuInicial()
//    {
//        menuPrincipal.onLoop = menuPrincipalOnLoop;
//        menuPrincipal.onEncdrDec = menuPrincipalOnEncdrDec;
//        menuPrincipal.onEncdrInc = menuPrincipalOnEncdrInc;
//        menuPrincipal.onClick = menuPrincipalOnClick;
//        menuPrincipal.onVoltar = menuPrincipalOnVoltar;
//    }
//}