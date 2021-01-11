#ifndef JARRON_H_
#define JARRON_H_

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cilindro con centro en el origen 

class Jarron : public ObjRevolucion
{
    public:
      Jarron(int num_instancias, bool con_tapas = true);
    
    private:
        float altura, radio;
} ;




#endif
