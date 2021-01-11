#ifndef KRILLIN_H_
#define KRILLIN_H_

#include "brazo.h"
#include "pierna.h"
#include "cabeza.h"

class Krillin
{
private:
    static const Tupla3f MAX_ROTACION_BRAZO_I;
    static const Tupla3f MIN_ROTACION_BRAZO_I;
    static const Tupla3f MAX_ROTACION_BRAZO_D;
    static const Tupla3f MIN_ROTACION_BRAZO_D;
    static const float MAX_ALTURA_BRAZO;
    static const float MIN_ALTURA_BRAZO;
    static const Tupla3f MAX_ROTACION_PIERNA_I;
    static const Tupla3f MIN_ROTACION_PIERNA_I;
    static const Tupla3f MAX_ROTACION_PIERNA_D;
    static const Tupla3f MIN_ROTACION_PIERNA_D;
    static const float MAX_ALTURA_CABEZA;
    static const float MIN_ALTURA_CABEZA;
    static const unsigned int NUM_GRADOS_LIBERTAD;
    static const Tupla4f AMBIENTE;
    static const Tupla4f DIFUSO;
    static const Tupla4f ESPECULAR;
    static const float BRILLO;
    Brazo *brazoD;
    Brazo *brazoI;
    Pierna *piernaD;
    Pierna *piernaI;
    Cabeza *cabeza;
    ObjPLY *torso;
    Tupla3f translacion;
    Tupla3f escala;
    Tupla3f rotacionBrazoD;
    Tupla3f rotacionBrazoI;
    Tupla3f rotacionPiernaD;
    Tupla3f rotacionPiernaI;
    float alturaBrazoI;
    float alturaBrazoD;
    float alturaCabeza;
    Tupla3f colorModoSelec;
    bool seleccionado;

public:
    Krillin();
    ~Krillin();
    void draw(bool modoSeleccion = false);
    void cambiar_dibujado(ModoDibujado modo);
    void cambiar_visualizacion(ModoVisualizacion modo);
    void toggleTapas();
    void toggleShadeMode();
    void rotarAntebrazoD(float grados, EnumEjes eje);
    void rotarBrazoD(float grados, EnumEjes eje);
    void subirBajarBrazoD(float altura);
    void rotarAntebrazoI(float grados, EnumEjes eje);
    void rotarBrazoI(float grados, EnumEjes eje);
    void subirBajarBrazoI(float altura);
    void rotarPieD(float grados, EnumEjes eje);
    void rotarPiernaD(float grados, EnumEjes eje);
    void rotarPieI(float grados, EnumEjes eje);
    void rotarPiernaI(float grados, EnumEjes eje);
    void rotarCabeza(float grados, EnumEjes eje);
    void subirBajarCabeza(float altura);
    void setColorModoSelec(Tupla3f color);
    void setSeleccionado(bool valor);
    void setMaterial(Material m);
    inline bool getSeleccionado()
    {
        return seleccionado;
    }
    inline const Tupla3f getMaxRotacionBrazoI() const
    {
        return MAX_ROTACION_BRAZO_I;
    }
    inline const Tupla3f getMinRotacionBrazoI() const
    {
        return MIN_ROTACION_BRAZO_I;
    }
    inline const Tupla3f getMaxRotacionBrazoD() const
    {
        return MAX_ROTACION_BRAZO_D;
    }
    inline const Tupla3f getMinRotacionBrazoD() const
    {
        return MIN_ROTACION_BRAZO_D;
    }
    inline const float getMaxAlturaBrazo() const
    {
        return MAX_ALTURA_BRAZO;
    }
    inline const float getMinAlturaBrazo() const
    {
        return MIN_ALTURA_BRAZO;
    }
    inline const Tupla3f getMaxRotacionPiernaI() const
    {
        return MAX_ROTACION_PIERNA_I;
    }
    inline const Tupla3f getMinRotacionPiernaI() const
    {
        return MIN_ROTACION_PIERNA_I;
    }
    inline const Tupla3f getMaxRotacionPiernaD() const
    {
        return MAX_ROTACION_PIERNA_D;
    }
    inline const Tupla3f getMinRotacionPiernaD() const
    {
        return MIN_ROTACION_PIERNA_D;
    }
    inline const float getMaxAlturaCabeza() const
    {
        return MAX_ALTURA_CABEZA;
    }
    inline const float getMinAlturaCabeza() const
    {
        return MIN_ALTURA_CABEZA;
    }
    inline const unsigned int getNumGradosLibertad() const
    {
        return NUM_GRADOS_LIBERTAD;
    }
    inline const Tupla3f getMaxGradosPieD() const
    {
        return piernaD->getMaxGradosPie();
    }
    inline const Tupla3f getMinGradosPieD() const
    {
        return piernaD->getMinGradosPie();
    }
    inline const Tupla3f getMaxGradosPieI() const
    {
        return piernaI->getMaxGradosPie();
    }
    inline const Tupla3f getMinGradosPieI() const
    {
        return piernaI->getMinGradosPie();
    }
    inline const Tupla3f getMaxGradosCabeza() const
    {
        return cabeza->getMaxGradosCabeza();
    }
    inline const Tupla3f getMinGradosCabeza() const
    {
        return cabeza->getMinGradosCabeza();
    }
    inline const Tupla3f getMaxGradosAntebrazoD() const
    {
        return brazoD->getMaxGradosAntebrazo();
    }
    inline const Tupla3f getMinGradosAntebrazoD() const
    {
        return brazoD->getMinGradosAntebrazo();
    }
    inline const Tupla3f getMaxGradosAntebrazoI() const
    {
        return brazoI->getMaxGradosAntebrazo();
    }
    inline const Tupla3f getMinGradosAntebrazoI() const
    {
        return brazoI->getMinGradosAntebrazo();
    }
    inline const Tupla3f getRotacionBrazoD() const
    {
        return rotacionBrazoD;
    }
    inline const Tupla3f getRotacionBrazoI() const
    {
        return rotacionBrazoI;
    }
    inline const Tupla3f getRotacionPiernaD() const
    {
        return rotacionPiernaD;
    }
    inline const Tupla3f getRotacionPiernaI() const
    {
        return rotacionPiernaI;
    }
    inline const Tupla3f getGradosAntebrazoD() const
    {
        return brazoD->getGradosAntebrazo();
    }
    inline const Tupla3f getGradosAntebrazoI() const
    {
        return brazoI->getGradosAntebrazo();
    }
    inline const Tupla3f getGradosPieD() const
    {
        return piernaD->getGradosPie();
    }
    inline const Tupla3f getGradosPieI() const
    {
        return piernaI->getGradosPie();
    }
    inline const Tupla3f getGradosCabeza() const
    {
        return cabeza->getGradosCabeza();
    }
    inline const float getAlturaCabeza() const
    {
        return alturaCabeza;
    }
    inline Tupla3f getColorModoSelec()
    {
        return colorModoSelec;
    }
};

#endif