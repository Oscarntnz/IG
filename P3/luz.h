#ifndef LUZ_H_
#define LUZ_H_

#include "aux.h"

class Luz{
    protected:
        GLenum id;
        Tupla4f posicion,
        colorAmbiente,
        colorDifuso,
        colorEspecular;
    public:
        virtual ~Luz() = default;
        void activar();
        void toggleEnabled();

        inline bool getActivada()const{
            return glIsEnabled(id);
        }
};

#endif