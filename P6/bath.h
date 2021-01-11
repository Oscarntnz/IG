#ifndef BATH_H_INCLUDED
#define BATH_H_INCLUDED

#include "aux.h"
#include "cubo.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class Bath : public Cubo
{

   public:
   Bath(float lado = 1);

} ;




#endif
