#ifndef CILINDRO_H_
#define CILINDRO_H_

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cilindro con centro en el origen 

class Cilindro: public ObjRevolucion
{
    public:
      Cilindro();
      Cilindro(const int num_vert_perfil = 2, const int num_instancias_perf = 20, 
      const float altura = 1.0, const float radio = 1.0, 
      EnumEjes eje_r = EnumEjes::E_Y, bool tapa_inf = true, bool tapa_sup = true);
    
    private:
        float altura, radio;
} ;




#endif
