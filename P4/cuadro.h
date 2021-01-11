#ifndef CUADRO_H_
#define CUADRO_H_

#include "aux.h"
#include "malla.h"

class Cuadro : public Malla3D
{
   public:
   Cuadro(float lado = 1, std::string textura = "text-madera");
};

#endif