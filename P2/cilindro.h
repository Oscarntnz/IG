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
      Cilindro(int num_vert_perfil = 2, int num_instancias_perf = 20, float h = 1.0, float r = 1.0);
    
    private:
        float altura, radio;
} ;




#endif
