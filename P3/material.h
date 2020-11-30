#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "aux.h"

class Material{
    private:
        Tupla4f ambiente,
        especular,
        difuso;
        float brillo;

    public:
        Material();
        Material(Tupla4f ambiente, Tupla4f difuso, Tupla4f especular, float brillo);
        void aplicar();

};

#endif