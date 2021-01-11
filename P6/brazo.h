#ifndef BRAZO_H_
#define BRAZO_H_

#include <string>
#include "objply.h"
#include "esfera.h"
#include "malla.h"

enum TipoExtremidad {IZQDA, DCHA};

class Brazo {
    private:
        Tupla3f MAX_GRADOS_ANTEBRAZO;
        Tupla3f MIN_GRADOS_ANTEBRAZO;
        TipoExtremidad tipo;
        ObjPLY * antebrazo;
        ObjPLY * biceps;
        Esfera * unionBrazo;
        Esfera * unionBiceps;
        Tupla3f gradosAntebrazo;
        Tupla3f translacion;
        Tupla3f escala;

    public:
        Brazo(TipoExtremidad tipo);
        ~Brazo();
        void rotarAnterazo(float grados, EnumEjes eje);
        void draw(bool modoSeleccion = false);
        void cambiar_dibujado(ModoDibujado modo);
        void cambiar_visualizacion(ModoVisualizacion modo);
        void toggleTapas();
        void toggleShadeMode();
        void setColorModoSelec(Tupla3f color);
        void setSeleccionado(bool valor);
        void setMaterial(Material mat);
        inline const Tupla3f getGradosAntebrazo()const{
            return gradosAntebrazo;
        }
        inline const Tupla3f getMaxGradosAntebrazo()const{
            return MAX_GRADOS_ANTEBRAZO;
        }
        inline const Tupla3f getMinGradosAntebrazo()const{
            return MIN_GRADOS_ANTEBRAZO;
        }
};

#endif