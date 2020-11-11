#ifndef CONO_H_
#define CONO_H_

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Tetraedro con centro en el origen 

class Cono: public ObjRevolucion
{
   private:
      float altura, radio;

   public:
      Cono(const int num_vert_perfil = 2, const int num_instancias_perf = 20, const float altura = 1.0, const float radio = 1.0, EnumEjes eje_r = EnumEjes::E_Y);

} ;




#endif
