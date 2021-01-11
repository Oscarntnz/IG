#include "brazo.h"
#include "aux.h"

Brazo::Brazo(TipoExtremidad tipo){
    this->tipo = tipo;
    gradosAntebrazo = {0.0, 0.0, 0.0};
    translacion = {0.0, 0.0, 0.0};
    escala = {0.0, 0.0, 0.0};

    if(tipo == TipoExtremidad::IZQDA){
        antebrazo = new ObjPLY("./plys/antebrazo_i");
        biceps = new ObjPLY("./plys/biceps_i");

        MAX_GRADOS_ANTEBRAZO = {-90.0, -90.0, -90.0};
        MIN_GRADOS_ANTEBRAZO = {90.0, 0.0, 90.0};
    }
    else{
        antebrazo = new ObjPLY("./plys/antebrazo_d");
        biceps = new ObjPLY("./plys/biceps_d");

        MAX_GRADOS_ANTEBRAZO = {90.0, 90.0, 90.0};
        MIN_GRADOS_ANTEBRAZO = {-90.0, 0.0, -90.0};
    }

    unionBrazo = new Esfera();
    unionBiceps = new Esfera();
}

Brazo::~Brazo(){
    delete antebrazo;
    delete biceps;
    delete unionBrazo;
    delete unionBiceps;
}

void Brazo::rotarAnterazo(float grados, EnumEjes eje){
    if(tipo == TipoExtremidad::DCHA){
        if((grados + gradosAntebrazo(eje)) > MAX_GRADOS_ANTEBRAZO(eje))
            gradosAntebrazo(eje) = MAX_GRADOS_ANTEBRAZO(eje);
        else if((grados + gradosAntebrazo(eje)) < MIN_GRADOS_ANTEBRAZO(eje))
            gradosAntebrazo(eje) = MIN_GRADOS_ANTEBRAZO(eje);
        else
            gradosAntebrazo(eje) += grados;
    }
    else{
       if((grados + gradosAntebrazo(eje)) < MAX_GRADOS_ANTEBRAZO(eje))
            gradosAntebrazo(eje) = MAX_GRADOS_ANTEBRAZO(eje);
        else if((grados + gradosAntebrazo(eje)) > MIN_GRADOS_ANTEBRAZO(eje))
            gradosAntebrazo(eje) = MIN_GRADOS_ANTEBRAZO(eje);
        else
            gradosAntebrazo(eje) += grados; 
    }
}

void Brazo::draw(bool modoSeleccion){
    translacion = {0.0, 0.0, 0.0};
    escala = {0.0, 0.0, 0.0};
    // Antebrazo + esfera
    glPushMatrix();
        glPushMatrix();
            glRotatef(gradosAntebrazo(EnumEjes::E_Z), 0, 0, 1);
            glRotatef(gradosAntebrazo(EnumEjes::E_Y), 0, 1, 0);
            glRotatef(gradosAntebrazo(EnumEjes::E_X), 1, 0, 0);

            if(tipo == TipoExtremidad::DCHA)
                translacion = {-1.61, 0, 0.07};
            else
                translacion = {1.61, 0.01, 0.08};

            glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));
            //Esfera
            glPushMatrix();
                if(tipo == TipoExtremidad::DCHA)
                    translacion = {1.22, 0, -0.08};
                else
                    translacion = {-1.22, 0, -0.08};

                escala = {0.39, 0.39, 0.39};
                
                glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

                glScalef(escala(EnumEjes::E_X), escala(EnumEjes::E_Y), escala(EnumEjes::E_Z));

                unionBrazo->draw(modoSeleccion);
            glPopMatrix();
            //Antebrazo
            glPushMatrix();
                antebrazo->draw(modoSeleccion);
            glPopMatrix();
        glPopMatrix();

        // Biceps + esfera
        glPushMatrix();
            // Esfera
            glPushMatrix();
                if(tipo == TipoExtremidad::DCHA)
                    translacion = {0.7, 0, -0.09};
                else
                    translacion = {-0.96, 0.04, -0.03};

                escala = {0.49, 0.49, 0.49};
                
                glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

                glScalef(escala(EnumEjes::E_X), escala(EnumEjes::E_Y), escala(EnumEjes::E_Z));

                unionBiceps->draw(modoSeleccion);
            glPopMatrix();
            // Biceps
            glPushMatrix();
                if(tipo == TipoExtremidad::DCHA)
                    translacion = {0.11, 0, -0.1};
                else
                    translacion = {-0.2, 0.02, -0.03};

                glTranslatef(translacion(EnumEjes::E_X), translacion(EnumEjes::E_Y), translacion(EnumEjes::E_Z));

                biceps->draw(modoSeleccion);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void Brazo::cambiar_dibujado(ModoDibujado modo){
    antebrazo->cambiar_dibujado(modo);
    biceps->cambiar_dibujado(modo);
    unionBrazo->cambiar_dibujado(modo);
    unionBiceps->cambiar_dibujado(modo);
}

void Brazo::cambiar_visualizacion(ModoVisualizacion modo){
    antebrazo->cambiar_visualizacion(modo);
    biceps->cambiar_visualizacion(modo);
    unionBrazo->cambiar_visualizacion(modo);
    unionBiceps->cambiar_visualizacion(modo);
}

void Brazo::toggleTapas(){
    unionBrazo->toggleTapas();
    unionBiceps->toggleTapas();
}

void Brazo::toggleShadeMode(){
    antebrazo->toggleShadeMode();
    biceps->toggleShadeMode();
    unionBrazo->toggleShadeMode();
    unionBiceps->toggleShadeMode();
}

void Brazo::setColorModoSelec(Tupla3f color){
    antebrazo->setColorModoSelec(color);
    biceps->setColorModoSelec(color);
    unionBrazo->setColorModoSelec(color);
    unionBiceps->setColorModoSelec(color);
}

void Brazo::setSeleccionado(bool valor){
    antebrazo->setSeleccionado(valor);
    biceps->setSeleccionado(valor);
    unionBrazo->setSeleccionado(valor);
    unionBiceps->setSeleccionado(valor);
}

void Brazo::setMaterial(Material mat){
    antebrazo->setMaterial(mat);
    biceps->setMaterial(mat);
    unionBrazo->setMaterial(mat);
    unionBiceps->setMaterial(mat);
}