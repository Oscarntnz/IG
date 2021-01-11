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
        void setColor(Tupla4f colorAmbiente, Tupla4f colorEspecular, Tupla4f colorDifuso);
        Tupla4f getColor(unsigned int indice)const;

        inline bool getActivada()const{
            return glIsEnabled(id);
        }
};

#endif