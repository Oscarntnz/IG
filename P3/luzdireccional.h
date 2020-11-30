#ifndef LUZ_DIRECCIONAL_H_
#define LUZ_DIRECCIONAL_H_

#include "aux.h"
#include "luz.h"

class LuzDireccional : public Luz{
    private:
        void ajustaAngulos();
        float gradARad(float grad);
        void calculaPos();

    protected:
        float alpha;
        float beta;

    public:
        LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular,
        Tupla4f colorDifuso);
        void variarAnguloAlpha(float incremento);
        void variarAnguloBeta(float incremento);
};

#endif