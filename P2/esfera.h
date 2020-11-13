#ifndef ESFERA_H_
#define ESFERA_H_

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Esfera con centro en el origen 

class Esfera: public ObjRevolucion
{
    public:
      Esfera();
      Esfera(const int num_vert_perfil = 10, const int num_instancias_perf = 20, const float radio = 1.0, 
      EnumEjes eje_r = EnumEjes::E_Y, bool con_tapas = true);
    
    private:
      float radio;
      Tupla3f calcularPuntoPerfilRotado(float factor_rotacion, Tupla3f polo);
};




#endif
