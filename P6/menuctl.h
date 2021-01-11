#ifndef _MENU_CTL_H
#define _MENU_CTL_H

#include <iostream>
#include <string>
#include "aux.h"

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
        void modoDibujado(std::string modo);
        void cambiado(std::string loCambiado);
        void noValido();
        void modoIluminacion();
        void cambiarAngulo(std::string angulo);
        void activadaLuz(bool activada, unsigned int i);
        void cambiadoSombreado(GLenum sombreado);
        void selGLib(unsigned int nGLib);
        void seleccionadoGrado(int i);
        void errorGrado();
        void selCamara(int nCam);
        void seleccionadaCamara(int i);
        void seleccionadoObjeto(int i);
};
#endif