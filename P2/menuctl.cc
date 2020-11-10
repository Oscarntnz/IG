#include "menuctl.h"
#include <iostream>
#include <string>

void MenuCtl::menuPrincipal(){
    std::cout << "Menu Principal:" << std::endl;
    std::cout << "\tD: Seleccion modo de dibujado" << std::endl;
    std::cout << "\tV: Seleccion modo de visualizacion" << std::endl;
    std::cout << "\tO: Seleccion de objeto" << std::endl;
    std::cout << "\tQ: Salir de la aplicacion" << std::endl;
}

void MenuCtl::selObjeto(){
    std::cout << "Modo seleccion de objeto:" << std::endl;
    std::cout << "\tC: Mostrar/ocultar cubo" << std::endl;
    std::cout << "\tT: Mostrar/ocultar tetraedro" << std::endl;
    std::cout << "\tP: Mostrar/ocultar objeto PLY" << std::endl;
    std::cout << "\tY: Mostrar/ocultar cono" << std::endl;
    std::cout << "\tH: Mostrar/ocultar cilindro" << std::endl;
}

void MenuCtl::muestraObjeto(std::string tipo, bool visible){
    std::cout << "\t" << (visible? "Mostrando" : "Ocultando") << " " << tipo << std::endl;
}

void MenuCtl::selVisualizacion(){
    std::cout << "Modo seleccion de visualizacion:" << std::endl;
    std::cout << "\tS: Modo solido" << std::endl;
    std::cout << "\tP: Modo puntos" << std::endl;
    std::cout << "\tL: Modo lineas" << std::endl;
    std::cout << "\tA: Modo ajedrez" << std::endl;
}

void MenuCtl::selDibujado(){
    std::cout << "Modo seleccion de dibujado:" << std::endl;
    std::cout << "\t1: Modo inmediato" << std::endl;
    std::cout << "\t2: Modo diferido" << std::endl;
}

void MenuCtl::modoDibujado(std::string modo){
    std::cout << "Modo de dibujado " << modo << std::endl;
}

void MenuCtl::cambiado(std::string loCambiado){
    std::cout << "Modo " << loCambiado << " cambiado" << std::endl;
}

void MenuCtl::noValido(){
    std::cout << "Opcion no valida" << std::endl;
}