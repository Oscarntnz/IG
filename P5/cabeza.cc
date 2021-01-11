#include "cabeza.h"
#include "aux.h"

const Tupla3f Cabeza::MAX_GRADOS_CABEZA = {45.0, 90.0, 45.0};
const Tupla3f Cabeza::MIN_GRADOS_CABEZA = {-45.0, -90.0, -45.0};

Cabeza::Cabeza(){
    gradosCabeza = {0.0, 0.0, 0.0};
    translacion = {0.0, 0.0, 0.0};
    escala = {0.0, 0.0, 0.0};

    cabeza = new ObjPLY("./plys/cabeza");
    cuello = new ObjPLY("./plys/cuello");

    unionCabeza = new Esfera();
}

Cabeza::~Cabeza(){
    delete cabeza;
    delete cuello;
    delete unionCabeza;
}

void Cabeza::rotarCabeza(float grados, EnumEjes eje){
    float alteracion = grados;

    if((alteracion + gradosCabeza(eje)) > MAX_GRADOS_CABEZA(eje))
        gradosCabeza(eje) = MAX_GRADOS_CABEZA(eje);
    else if((alteracion + gradosCabeza(eje)) < MIN_GRADOS_CABEZA(eje))
        gradosCabeza(eje) = MIN_GRADOS_CABEZA(eje);
    else
        gradosCabeza(eje) += grados;
}

void Cabeza::draw(){
    translacion = {0.0, 0.0, 0.0};
    escala = {0.0, 0.0, 0.0};
    
    glPushMatrix();
        // Cabeza + esfera
        glPushMatrix();
            translacion = {0.0, 0.6, 0.0};
            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

            glRotatef(gradosCabeza(EnumEjes::E_Z), 0, 0, 1);
            glRotatef(gradosCabeza(EnumEjes::E_Y), 0, 1, 0);
            glRotatef(gradosCabeza(EnumEjes::E_X), 1, 0, 0);
            glTranslatef(0, -0.1*fabs(gradosCabeza(EnumEjes::E_Y)/90.0), 0);

            translacion = {0.0, 2.06, 0.24};
            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

            //Esfera
            glPushMatrix();
                translacion = {0.0, -1.06, -0.25};
                glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

                unionCabeza->draw();
            glPopMatrix();
            // Cabeza
            glPushMatrix();
                cabeza->draw();
            glPopMatrix();
        glPopMatrix();

        // Cuello
        glPushMatrix();
            translacion = {0.0, 0.66, 0.0};
            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

            cuello->draw();
        glPopMatrix();
    glPopMatrix();
}

void Cabeza::cambiar_dibujado(ModoDibujado modo){
    cabeza->cambiar_dibujado(modo);
    cuello->cambiar_dibujado(modo);
    unionCabeza->cambiar_dibujado(modo);
}

void Cabeza::cambiar_visualizacion(ModoVisualizacion modo){
    cabeza->cambiar_visualizacion(modo);
    cuello->cambiar_visualizacion(modo);
    unionCabeza->cambiar_visualizacion(modo);
}

void Cabeza::toggleTapas(){
    unionCabeza->toggleTapas();
}

void Cabeza::toggleShadeMode(){
    cabeza->toggleShadeMode();
    cuello->toggleShadeMode();
    unionCabeza->toggleShadeMode();
}