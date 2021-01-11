#ifndef PIERNA_H_
#define PIERNA_H_

#include <string>
#include "aux.h"
#include "objply.h"
#include "esfera.h"
#include "brazo.h"

class Pierna {
    private:
        static const Tupla3f MAX_GRADOS_PIE;
        static const Tupla3f MIN_GRADOS_PIE;
        TipoExtremidad tipo;
        ObjPLY * pie;
        ObjPLY * cuadriceps;
        Esfera * unionPie;
        Esfera * unionCuadriceps;
        Tupla3f gradosPie;
        Tupla3f translacion;
        Tupla3f escala;

    public:
        Pierna(TipoExtremidad tipo);
        virtual ~Pierna();
        void rotarPie(float grados, EnumEjes eje);
        virtual void draw();
        void cambiar_dibujado(ModoDibujado modo);
        void cambiar_visualizacion(ModoVisualizacion modo);
        void toggleTapas();
        void toggleShadeMode();
        inline const Tupla3f getGradosPie()const{
            return gradosPie;
        }
        inline const Tupla3f getMaxGradosPie()const{
            return MAX_GRADOS_PIE;
        }
        inline const Tupla3f getMinGradosPie()const{
            return MIN_GRADOS_PIE;
        }
};

#endif