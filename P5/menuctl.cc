#include "menuctl.h"
#include <iostream>
#include <string>

void MenuCtl::menuPrincipal(){
    std::cout << "Menu Principal:" << std::endl;
    std::cout << "\tD: Seleccion modo de dibujado" << std::endl;
    std::cout << "\tV: Seleccion modo de visualizacion" << std::endl;
    std::cout << "\tO: Seleccion de objeto" << std::endl;
    std::cout << "\tT: Cambiar tapas" << std::endl;
    std::cout << "\tI: Cambiar iluminacion" << std::endl;
    std::cout << "\tM: Mover manualmente grado lib." << std::endl;
    std::cout << "\tA: Animacion automatica grados lib." << std::endl;
    std::cout << "\tQ: Salir de la aplicacion" << std::endl;
}

void MenuCtl::selObjeto(){
    std::cout << "Modo seleccion de objeto:" << std::endl;
    std::cout << "\tC: Mostrar/ocultar cubo" << std::endl;
    std::cout << "\tT: Mostrar/ocultar tetraedro" << std::endl;
    std::cout << "\tP: Mostrar/ocultar objeto PLY" << std::endl;
    std::cout << "\tY: Mostrar/ocultar cono" << std::endl;
    std::cout << "\tH: Mostrar/ocultar cilindro" << std::endl;
    std::cout << "\tE: Mostrar/ocultar esfera" << std::endl;
    std::cout << "\tR: Mostrar/ocultar objeto revolución" << std::endl;
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

void MenuCtl::selTapa(){
    std::cout << "\t" << "Cambiada tapas" << std::endl;
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

void MenuCtl::modoIluminacion(){
    std::cout << "Modo seleccion de iluminacion:" << std::endl;
    std::cout << "\t0: Cambiar Luz Posicional" << std::endl;
    std::cout << "\t1: Cambiar Luz Direccional" << std::endl;
    std::cout << "\tA: Variar Angulo Alpha" << std::endl;
    std::cout << "\tB: Variar Angulo Beta" << std::endl;
    std::cout << "\tS: Cambiar modo sombreado" << std::endl;
}

void MenuCtl::cambiarAngulo(std::string angulo){
    std::cout << "Modo variacion de angulo " << angulo << ":" << std::endl;
    std::cout << "\t>: Incrementar angulo" << std::endl;
    std::cout << "\t<: Decrementar angulo" << std::endl;
}

void MenuCtl::activadaLuz(bool activada, unsigned int i){
    std::cout << "\t" << (activada? "Activada" : "Desactivada") << " luz " << i << std::endl;
}

void MenuCtl::cambiadoSombreado(GLenum sombreado){
    std::cout << "\tModo sombreado " << (sombreado == GL_SMOOTH? "suave" : "plano") << std::endl;
}

void MenuCtl::selGLib(unsigned int nGLib){
    std::cout << "\nSeleccionar grado de libertad(0 - " << nGLib << ")" << std::endl;
}

void MenuCtl::seleccionadoGrado(int i){
    std::cout << "\nSeleccionado grado de libertad: " << i << std::endl;
}

void MenuCtl::errorGrado(){
    std::cout << "\nNo valido para ese grado"<< std::endl;
}