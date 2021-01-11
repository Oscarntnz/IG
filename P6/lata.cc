#include "lata.h"

Lata::Lata(bool conTapas){
    cuerpo = new ObjRevolucion("plys/lata-pcue", 30, EnumEjes::E_Y, false, false, false);
    pSup = new ObjRevolucion("plys/lata-psup", 30, EnumEjes::E_Y, false, false, false);
    pInf = new ObjRevolucion("plys/lata-pinf", 30, EnumEjes::E_Y, false, false, false);

    seleccionado = false;
    this->conTapas = conTapas;
    pSup->setColor({0.25, 0.25, 0.25}, {0.25, 0.25, 0.25});
    pInf->setColor({0.25, 0.25, 0.25}, {0.25, 0.25, 0.25});
}

Lata::~Lata(){
    delete cuerpo;
    delete pSup;
    delete pInf;
}

void Lata::draw(bool modoSeleccion){
    cuerpo->draw(modoSeleccion);

    if(conTapas){
        pSup->draw(modoSeleccion);
        pInf->draw(modoSeleccion);
    }
}

void Lata::cambiar_dibujado(ModoDibujado modo){
    cuerpo->cambiar_dibujado(modo);
    pSup->cambiar_dibujado(modo);
    pInf->cambiar_dibujado(modo);
}

void Lata::cambiar_visualizacion(ModoVisualizacion modo){
    cuerpo->cambiar_visualizacion(modo);
    pSup->cambiar_visualizacion(modo);
    pInf->cambiar_visualizacion(modo);
}

void Lata::toggleTapas(){
    conTapas = !conTapas;
}

void Lata::toggleShadeMode(){
    cuerpo->toggleShadeMode();
    pSup->toggleShadeMode();
    pInf->toggleShadeMode();
}

void Lata::setColorModoSelec(Tupla3f color){
    colorModoSelec = color;

    cuerpo->setColorModoSelec(color);
    pSup->setColorModoSelec(color);
    pInf->setColorModoSelec(color);
}

void Lata::setSeleccionado(bool valor){
    seleccionado = valor;

    cuerpo->setSeleccionado(valor);
    pSup->setSeleccionado(valor);
    pInf->setSeleccionado(valor);
}

void Lata::setTextura(std::string archivo){
    cuerpo->setTextura(archivo);
    cuerpo->calcularPuntosTex();
}