#ifndef LUZ_POS_H_
#define LUZ_POS_H_

#include "aux.h"
#include "luz.h"

class LuzPosicional : public Luz{
    public:
        LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular,
        Tupla4f colorDifuso);
};

#endif