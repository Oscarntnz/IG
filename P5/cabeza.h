#ifndef CABEZA_H_
#define CABEZA_H_

#include <string>
#include "aux.h"
#include "objply.h"
#include "esfera.h"

class Cabeza {
    private:
        static const Tupla3f MAX_GRADOS_CABEZA;
        static const Tupla3f MIN_GRADOS_CABEZA;
        ObjPLY * cabeza;
        ObjPLY * cuello;
        Esfera * unionCabeza;
        Tupla3f gradosCabeza;
        Tupla3f translacion;
        Tupla3f escala;

    public:
        Cabeza();
        ~Cabeza();
        void rotarCabeza(float grados, EnumEjes eje);
        void draw();
        void cambiar_dibujado(ModoDibujado modo);
        void cambiar_visualizacion(ModoVisualizacion modo);
        void toggleTapas();
        void toggleShadeMode();
        inline const Tupla3f getGradosCabeza()const{
            return gradosCabeza;
        }
        inline const Tupla3f getMaxGradosCabeza()const{
            return MAX_GRADOS_CABEZA;
        }
        inline const Tupla3f getMinGradosCabeza()const{
            return MIN_GRADOS_CABEZA;
        }
};

#endif