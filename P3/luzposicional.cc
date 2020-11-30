#include "luzposicional.h"

LuzPosicional::LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular,
Tupla4f colorDifuso){
    this->id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorAmbiente = colorAmbiente;

    this->posicion = {posicion(EnumEjes::E_X), posicion(EnumEjes::E_Y), posicion(EnumEjes::E_Z), 1.0};
}