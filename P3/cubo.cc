#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   // inicializar la tabla de vértices

   v.push_back({-lado/2,lado/2,lado/2}); v.push_back({-lado/2,-lado/2,lado/2}); v.push_back({lado/2,-lado/2,lado/2});
   v.push_back({lado/2,lado/2,lado/2}); v.push_back({lado/2,lado/2,-lado/2}); v.push_back({-lado/2,lado/2,-lado/2});
   v.push_back({-lado/2,-lado/2,-lado/2}); v.push_back({lado/2,-lado/2,-lado/2});

   // inicializar la tabla de caras o triángulos:

   //Frontal
   f.push_back({2,0,1}); f.push_back({2,3,0});
   //Derecha
   f.push_back({3,2,7}); f.push_back({3,7,4}); 
   //Trasera
   f.push_back({6,4,7}); f.push_back({6,5,4});
   //Izquierda
   f.push_back({5,6,1}); f.push_back({5,1,0});
   //Inferior
   f.push_back({1,6,7}); f.push_back({1,7,2});
   //Superior
   f.push_back({5,0,3}); f.push_back({5,3,4});

   rellenar_vectores();
}

