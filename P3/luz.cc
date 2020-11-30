#include "luz.h"

void Luz::activar(){
    if(this->getActivada()){
        glPushMatrix();
            glLightfv(id, GL_DIFFUSE, colorDifuso);
            glLightfv(id, GL_AMBIENT, colorAmbiente);
            glLightfv(id, GL_SPECULAR, colorEspecular);
            glLightfv(id, GL_POSITION, posicion);
        glPopMatrix();
    }
}

void Luz::toggleEnabled(){
    if(getActivada())
        glDisable(id);
    else
        glEnable(id);    
}