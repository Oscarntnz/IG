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

void Luz::setColor(Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso){
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorDifuso = colorDifuso;
}

Tupla4f Luz::getColor(unsigned int indice)const{
    if(indice == 0){
        return this->colorAmbiente;
    }
    else if(indice == 1){
        return this->colorEspecular;
    }
    else{
        return this->colorDifuso;
    }    
}