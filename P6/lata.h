#ifndef LATA_H_
#define LATA_H_

#include "objrevolucion.h"

class Lata
{
private:
    ObjRevolucion *cuerpo;
    ObjRevolucion *pSup;
    ObjRevolucion *pInf;
    Tupla3f colorModoSelec;
    bool seleccionado;
    bool conTapas;

public:
    Lata(bool conTapas);
    ~Lata();
    void draw(bool modoSeleccion = false);
    void cambiar_dibujado(ModoDibujado modo);
    void cambiar_visualizacion(ModoVisualizacion modo);
    void toggleTapas();
    void toggleShadeMode();
    void setColorModoSelec(Tupla3f color);
    void setSeleccionado(bool valor);
    void setTextura(std::string archivo);
    inline bool getSeleccionado()
    {
        return seleccionado;
    }
    inline Tupla3f getColorModoSelec()
    {
        return colorModoSelec;
    }
};

#endif