#ifndef _MENU_CTL_H
#define _MENU_CTL_H

#include <iostream>
#include <string>

class MenuCtl
{
    private:

    public:
        void menuPrincipal();
        void selObjeto();
        void muestraObjeto(std::string tipo, bool visible);
        void selVisualizacion();
        void selDibujado();
        void selTapa();
        void muestraTapa(std::string tapa);
        void modoDibujado(std::string modo);
        void cambiado(std::string loCambiado);
        void noValido();
};
#endif