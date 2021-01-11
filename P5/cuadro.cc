#include "aux.h"
#include "malla.h"
#include "cuadro.h"

Cuadro::Cuadro(float lado, std::string textura)
{
   // inicializar la tabla de vértices

   v.push_back({-lado/2, lado/2, 0}); v.push_back({-lado/2, -lado/2, 0}); v.push_back({lado/2, -lado/2, 0});
   v.push_back({lado/2, lado/2, 0});

   // inicializar la tabla de caras o triángulos:

   f.push_back({2,0,1}); f.push_back({2,3,0});

   rellenar_vectores();
   setTextura(textura);

   ct[0] = {0.0, 0.0}; ct[1] = {0.0, 1.0};
   ct[2] = {1.0, 1.0}; ct[3] = {1.0, 0.0};
}

