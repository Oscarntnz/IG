#include "krillin.h"

const Tupla3f Krillin::MAX_ROTACION_BRAZO_I = {90.0, 45.0, 90.0};
const Tupla3f Krillin::MIN_ROTACION_BRAZO_I = {-180.0, -90.0, -90.0};
const Tupla3f Krillin::MAX_ROTACION_BRAZO_D = {180.0, 90.0, 90.0};
const Tupla3f Krillin::MIN_ROTACION_BRAZO_D = {-90.0, -45.0, -90.0};
const float Krillin::MAX_ALTURA_BRAZO = 0.2;
const float Krillin::MIN_ALTURA_BRAZO = -0.2;
const Tupla3f Krillin::MAX_ROTACION_PIERNA_I = {90.0, 0.0, 90.0};
const Tupla3f Krillin::MIN_ROTACION_PIERNA_I = {-90.0, 0.0, 0.0};
const Tupla3f Krillin::MAX_ROTACION_PIERNA_D = {90.0, 0.0, 90.0};
const Tupla3f Krillin::MIN_ROTACION_PIERNA_D = {-90.0, 0.0, 0.0};
const float Krillin::MAX_ALTURA_CABEZA = 0.1;
const float Krillin::MIN_ALTURA_CABEZA = -0.3;
const unsigned int Krillin::NUM_GRADOS_LIBERTAD = 26;
const Tupla4f Krillin::AMBIENTE = {0.0, 0.05, 0.05, 1.0};
const Tupla4f Krillin::DIFUSO = {0.4, 0.5, 0.5, 1.0};
const Tupla4f Krillin::ESPECULAR = {0.04, 0.7, 0.7, 1.0};
const float Krillin::BRILLO = 0.078125*128;

Krillin::Krillin(){
    brazoD = new Brazo(TipoExtremidad::DCHA);
    brazoI = new Brazo(TipoExtremidad::IZQDA);
    piernaD = new Pierna(TipoExtremidad::DCHA);
    piernaI = new Pierna(TipoExtremidad::IZQDA);
    cabeza = new Cabeza();
    torso = new ObjPLY("./plys/torso");

    translacion = {0.0, 0.0, 0.0};
    escala = {0.0, 0.0, 0.0};
    rotacionBrazoD = {0.0, 0.0, 0.0};
    rotacionBrazoI = {0.0, 0.0, 0.0};
    rotacionPiernaD = {0.0, 0.0, 0.0};
    rotacionPiernaI = {0.0, 0.0, 0.0};
    alturaBrazoI = 0.0;
    alturaBrazoD = 0.0;
    alturaCabeza = 0.0;
    seleccionado = false;

    Material mat(AMBIENTE, DIFUSO, ESPECULAR, BRILLO);

    this->setMaterial(mat);
}

Krillin::~Krillin(){
    delete brazoD;
    delete brazoI;
    delete piernaD;
    delete piernaI;
    delete cabeza;
    delete torso;
}

void Krillin::draw(bool modoSeleccion){
    translacion = {0.0, 0.0, 0.0};
    escala = {1.0, 1.0, 1.0};

    glPushMatrix();
        // Brazo D
        glPushMatrix();
            translacion = {-1.49, 0.88, 0};
            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

            glTranslatef(0.0, alturaBrazoD, 0.0);

            translacion = {(float)((rotacionBrazoD(EnumEjes::E_Y) > 0.0? -rotacionBrazoD(EnumEjes::E_Y)/(2* MAX_ROTACION_BRAZO_D(EnumEjes::E_Y)) : -rotacionBrazoD(EnumEjes::E_Y)/(2*MIN_ROTACION_BRAZO_D(EnumEjes::E_Y))) + (rotacionBrazoD(EnumEjes::E_Z) > 0.0? -rotacionBrazoD(EnumEjes::E_Z)/(2* MAX_ROTACION_BRAZO_D(EnumEjes::E_Z)) : -rotacionBrazoD(EnumEjes::E_Z)/(2*MIN_ROTACION_BRAZO_D(EnumEjes::E_Z)))),
            (float)(rotacionBrazoD(EnumEjes::E_Z) > 0.0? rotacionBrazoD(EnumEjes::E_Z)/(2* MAX_ROTACION_BRAZO_D(EnumEjes::E_Z)) : -rotacionBrazoD(EnumEjes::E_Z)/(2*MIN_ROTACION_BRAZO_D(EnumEjes::E_Z))),
            (float)(rotacionBrazoD(EnumEjes::E_Y) > 0.0? -rotacionBrazoD(EnumEjes::E_Y)/(2* MAX_ROTACION_BRAZO_D(EnumEjes::E_Y)) : rotacionBrazoD(EnumEjes::E_Y)/(2*MIN_ROTACION_BRAZO_D(EnumEjes::E_Y)))};

            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

            glRotatef(rotacionBrazoD(EnumEjes::E_Z), 0, 0, 1);
            glRotatef(rotacionBrazoD(EnumEjes::E_Y), 0, 1, 0);
            glRotatef(rotacionBrazoD(EnumEjes::E_X), 1, 0, 0);

            translacion = {-1.19, -0.01, 0.08};
            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

            brazoD->draw(modoSeleccion);
        glPopMatrix();
        // Brazo I
        glPushMatrix();
            translacion = {1.49, 0.84, -0.09};
            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

            glTranslatef(0.0, alturaBrazoI, 0.0);

            translacion = {(float)((rotacionBrazoI(EnumEjes::E_Y) > 0.0? rotacionBrazoI(EnumEjes::E_Y)/(2* MAX_ROTACION_BRAZO_I(EnumEjes::E_Y)) : rotacionBrazoI(EnumEjes::E_Y)/(2*MIN_ROTACION_BRAZO_I(EnumEjes::E_Y))) + (rotacionBrazoI(EnumEjes::E_Z) > 0.0? rotacionBrazoI(EnumEjes::E_Z)/(2* MAX_ROTACION_BRAZO_I(EnumEjes::E_Z)) : rotacionBrazoI(EnumEjes::E_Z)/(2*MIN_ROTACION_BRAZO_I(EnumEjes::E_Z)))),
            (float)(rotacionBrazoI(EnumEjes::E_Z) > 0.0? -rotacionBrazoI(EnumEjes::E_Z)/(2* MAX_ROTACION_BRAZO_I(EnumEjes::E_Z)) : rotacionBrazoI(EnumEjes::E_Z)/(2*MIN_ROTACION_BRAZO_I(EnumEjes::E_Z))),
            (float)(rotacionBrazoI(EnumEjes::E_Y) > 0.0? rotacionBrazoI(EnumEjes::E_Y)/(2* MAX_ROTACION_BRAZO_I(EnumEjes::E_Y)) : -rotacionBrazoI(EnumEjes::E_Y)/(2*MIN_ROTACION_BRAZO_I(EnumEjes::E_Y)))};

            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

            glRotatef(rotacionBrazoI(EnumEjes::E_Z), 0, 0, 1);
            glRotatef(rotacionBrazoI(EnumEjes::E_Y), 0, 1, 0);
            glRotatef(rotacionBrazoI(EnumEjes::E_X), 1, 0, 0);
 
            translacion = {1.45, -0.04, 0.03};
            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

            brazoI->draw(modoSeleccion);
        glPopMatrix();
        // Pierna D
        glPushMatrix();
            translacion = {-0.74, 0.0, 0.3};
            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

            glRotatef(rotacionPiernaD(EnumEjes::E_Z), 0, 0, 1);
            glRotatef(rotacionPiernaD(EnumEjes::E_Y), 0, 1, 0);
            glRotatef(rotacionPiernaD(EnumEjes::E_X), 1, 0, 0);

            translacion = {-0.24, -1.54, 0.01};
            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

            piernaD->draw(modoSeleccion);
        glPopMatrix();
        // Pierna I
        glPushMatrix();
            translacion = {0.75, 0.0, 0.29};
            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

            glRotatef(rotacionPiernaI(EnumEjes::E_Z), 0, 0, 1);
            glRotatef(rotacionPiernaI(EnumEjes::E_Y), 0, 1, 0);
            glRotatef(rotacionPiernaI(EnumEjes::E_X), 1, 0, 0);

            translacion = {0.18, -1.35, 0.02};
            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

            piernaI->draw(modoSeleccion);
        glPopMatrix();
        // Cabeza
        glPushMatrix();
            translacion = {0.0, 1.12, -0.19};
            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

            
            translacion = {0.0, alturaCabeza, 0.0};
            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

            cabeza->draw(modoSeleccion);
        glPopMatrix();
        // Torso
        glPushMatrix();
            translacion = {0.0, 0.29, 0.13};
            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

            torso->draw(modoSeleccion);
        glPopMatrix();
    glPopMatrix();
}

void Krillin::cambiar_dibujado(ModoDibujado modo){
    brazoD->cambiar_dibujado(modo);
    brazoI->cambiar_dibujado(modo);
    piernaD->cambiar_dibujado(modo);
    piernaI->cambiar_dibujado(modo);
    cabeza->cambiar_dibujado(modo);
    torso->cambiar_dibujado(modo);
}

void Krillin::cambiar_visualizacion(ModoVisualizacion modo){
    brazoD->cambiar_visualizacion(modo);
    brazoI->cambiar_visualizacion(modo);
    piernaD->cambiar_visualizacion(modo);
    piernaI->cambiar_visualizacion(modo);
    cabeza->cambiar_visualizacion(modo);
    torso->cambiar_visualizacion(modo);
}

void Krillin::toggleTapas(){
    brazoD->toggleTapas();
    brazoI->toggleTapas();
    piernaD->toggleTapas();
    piernaI->toggleTapas();
    cabeza->toggleTapas();
}

void Krillin::toggleShadeMode(){
    brazoD->toggleShadeMode();
    brazoI->toggleShadeMode();
    piernaD->toggleShadeMode();
    piernaI->toggleShadeMode();
    cabeza->toggleShadeMode();
    torso->toggleShadeMode();
}

void Krillin::rotarAntebrazoD(float grados, EnumEjes eje){
    brazoD->rotarAnterazo(grados, eje);
}

void Krillin::rotarBrazoD(float grados, EnumEjes eje){
    if((grados + rotacionBrazoD(eje)) > MAX_ROTACION_BRAZO_D(eje))
        rotacionBrazoD(eje) = MAX_ROTACION_BRAZO_D(eje);
    else if((grados + rotacionBrazoD(eje)) < MIN_ROTACION_BRAZO_D(eje))
        rotacionBrazoD(eje) = MIN_ROTACION_BRAZO_D(eje);
    else
        rotacionBrazoD(eje) += grados;
}

void Krillin::subirBajarBrazoD(float altura){
    if((altura + alturaBrazoD) > MAX_ALTURA_BRAZO)
        alturaBrazoD = MAX_ALTURA_BRAZO;
    else if((altura + alturaBrazoD) < MIN_ALTURA_BRAZO)
        alturaBrazoD = MIN_ALTURA_BRAZO;
    else
        alturaBrazoD += altura;
}

void Krillin::rotarAntebrazoI(float grados, EnumEjes eje){
    brazoI->rotarAnterazo(grados, eje);
}

void Krillin::rotarBrazoI(float grados, EnumEjes eje){
    if((grados + rotacionBrazoI(eje)) > MAX_ROTACION_BRAZO_I(eje))
        rotacionBrazoI(eje) = MAX_ROTACION_BRAZO_I(eje);
    else if((grados + rotacionBrazoI(eje)) < MIN_ROTACION_BRAZO_I(eje))
        rotacionBrazoI(eje) = MIN_ROTACION_BRAZO_I(eje);
    else
        rotacionBrazoI(eje) += grados;
}

void Krillin::subirBajarBrazoI(float altura){
    if((altura + alturaBrazoI) > MAX_ALTURA_BRAZO)
        alturaBrazoI = MAX_ALTURA_BRAZO;
    else if((altura + alturaBrazoI) < MIN_ALTURA_BRAZO)
        alturaBrazoI = MIN_ALTURA_BRAZO;
    else
        alturaBrazoI += altura;
}

void Krillin::rotarPieD(float grados, EnumEjes eje){
    piernaD->rotarPie(grados, eje);
}

void Krillin::rotarPiernaD(float grados, EnumEjes eje){
    if((grados + rotacionPiernaD(eje)) > MAX_ROTACION_PIERNA_D(eje))
        rotacionPiernaD(eje) = MAX_ROTACION_PIERNA_D(eje);
    else if((grados + rotacionPiernaD(eje)) < MIN_ROTACION_PIERNA_D(eje))
        rotacionPiernaD(eje) = MIN_ROTACION_PIERNA_D(eje);
    else
        rotacionPiernaD(eje) += grados;
}

void Krillin::rotarPieI(float grados, EnumEjes eje){
    piernaI->rotarPie(grados, eje);
}

void Krillin::rotarPiernaI(float grados, EnumEjes eje){
    if((grados + rotacionPiernaI(eje)) > MAX_ROTACION_PIERNA_I(eje))
        rotacionPiernaI(eje) = MAX_ROTACION_PIERNA_I(eje);
    else if((grados + rotacionPiernaI(eje)) < MIN_ROTACION_PIERNA_I(eje))
        rotacionPiernaI(eje) = MIN_ROTACION_PIERNA_I(eje);
    else
        rotacionPiernaI(eje) += grados;
}

void Krillin::rotarCabeza(float grados, EnumEjes eje){
    cabeza->rotarCabeza(grados, eje);
}

void Krillin::subirBajarCabeza(float altura){
    if((altura + alturaCabeza) > MAX_ALTURA_CABEZA)
        alturaCabeza = MAX_ALTURA_CABEZA;
    else if((altura + alturaCabeza) < MIN_ALTURA_CABEZA)
        alturaCabeza = MIN_ALTURA_CABEZA;
    else
        alturaCabeza += altura;
}

void Krillin::setColorModoSelec(Tupla3f color){
    colorModoSelec = color;

    brazoD->setColorModoSelec(color);
    brazoI->setColorModoSelec(color);
    piernaD->setColorModoSelec(color);
    piernaI->setColorModoSelec(color);
    cabeza->setColorModoSelec(color);
    torso->setColorModoSelec(color);
}

void Krillin::setSeleccionado(bool valor){
    seleccionado = valor;

    brazoD->setSeleccionado(valor);
    brazoI->setSeleccionado(valor);
    piernaD->setSeleccionado(valor);
    piernaI->setSeleccionado(valor);
    cabeza->setSeleccionado(valor);
    torso->setSeleccionado(valor);
}

void Krillin::setMaterial(Material mat){
    brazoD->setMaterial(mat);
    brazoI->setMaterial(mat);
    piernaD->setMaterial(mat);
    piernaI->setMaterial(mat);
    cabeza->setMaterial(mat);
    torso->setMaterial(mat);
}