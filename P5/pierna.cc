#include "pierna.h"
#include "aux.h"

const Tupla3f Pierna::MAX_GRADOS_PIE = {90.0, 0.0, 90.0};
const Tupla3f Pierna::MIN_GRADOS_PIE = {-90.0, 0.0, 0.0};

Pierna::Pierna(TipoExtremidad tipo){
    this->tipo = tipo;
    gradosPie = {0.0, 0.0, 0.0};
    translacion = {0.0, 0.0, 0.0};
    escala = {0.0, 0.0, 0.0};

    if(tipo == TipoExtremidad::IZQDA){
        pie = new ObjPLY("./plys/pie_i");
        cuadriceps = new ObjPLY("./plys/cuadriceps_i");
    }
    else{
        pie = new ObjPLY("./plys/pie_d");
        cuadriceps = new ObjPLY("./plys/cuadriceps_d");
    }

    unionPie = new Esfera();
    unionCuadriceps = new Esfera();
}

Pierna::~Pierna(){
    delete pie;
    delete cuadriceps;
    delete unionPie;
    delete unionCuadriceps;
}

void Pierna::rotarPie(float grados, EnumEjes eje){
    if((grados + gradosPie(eje)) > MAX_GRADOS_PIE(eje))
        gradosPie(eje) = MAX_GRADOS_PIE(eje);
    else if((grados + gradosPie(eje)) < MIN_GRADOS_PIE(eje))
        gradosPie(eje) = MIN_GRADOS_PIE(eje);
    else
        gradosPie(eje) += grados;
}


void Pierna::draw(){
    translacion = {0.0, 0.0, 0.0};
    escala = {0.0, 0.0, 0.0};

    glPushMatrix();
        // Pie + esfera
        glPushMatrix();
            glRotatef(gradosPie(EnumEjes::E_Z), 0, 0, 1);
            glRotatef(gradosPie(EnumEjes::E_Y), 0, 1, 0);
            glRotatef(gradosPie(EnumEjes::E_X), 1, 0, 0);

            if(tipo == TipoExtremidad::DCHA)
                translacion = {-0.19, -2.19, -0.03};
            else
                translacion = {0.24, -2.23, 0.01};

            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));
            //Esfera
            glPushMatrix();
                if(tipo == TipoExtremidad::DCHA)
                    translacion = {0.2, 1.19, 0.02};
                else
                    translacion = {-0.23, 1.23, 0};

                escala = {1.0, 1.0, 1.18};
                
                glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

                glScalef(escala(EnumEjes::E_X), escala(EnumEjes::E_Y), escala(EnumEjes::E_Z));

                unionPie->draw();
            glPopMatrix();
            // Pie
            glPushMatrix();
                pie->draw();
            glPopMatrix();
        glPopMatrix();

        // Cuadriceps + esfera
        glPushMatrix();
            // Esfera
            glPushMatrix();
                if(tipo == TipoExtremidad::DCHA){
                    translacion = {0.24, 0.88, 0.0};
                    escala = {0.71, 0.66, 1.0};
                }
                else{
                    translacion = {-0.16, 0.74, 0.04};
                    escala = {0.82, 0.71, 1.21};
                }                
                
                glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

                glScalef(escala(EnumEjes::E_X), escala(EnumEjes::E_Y), escala(EnumEjes::E_Z));

                unionCuadriceps->draw();
            glPopMatrix();
            // Cuadriceps
            glPushMatrix();
                if(tipo == TipoExtremidad::DCHA)
                    translacion = {0.19, -0.17, 0.05};
                else
                    translacion = {-0.19, -0.22, 0.12};

                glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

                cuadriceps->draw();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Pierna::cambiar_dibujado(ModoDibujado modo){
    pie->cambiar_dibujado(modo);
    cuadriceps->cambiar_dibujado(modo);
    unionPie->cambiar_dibujado(modo);
    unionCuadriceps->cambiar_dibujado(modo);
}

void Pierna::cambiar_visualizacion(ModoVisualizacion modo){
    pie->cambiar_visualizacion(modo);
    cuadriceps->cambiar_visualizacion(modo);
    unionPie->cambiar_visualizacion(modo);
    unionCuadriceps->cambiar_visualizacion(modo);
}

void Pierna::toggleTapas(){
    unionPie->toggleTapas();
    unionCuadriceps->toggleTapas();
}

void Pierna::toggleShadeMode(){
    pie->toggleShadeMode();
    cuadriceps->toggleShadeMode();
    unionPie->toggleShadeMode();
    unionCuadriceps->toggleShadeMode();
}