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
   public:
      Cono(float altura = 1, float radio = 1, int num_instancias = 5, bool tapa_i = true, EnumEjes eje_r = EnumEjes::E_Y);

} ;




#endif
