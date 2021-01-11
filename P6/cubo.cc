#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   // inicializar la tabla de vértices

   // ABCDEFGH
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

   // BBCGGH
   v.push_back({-lado/2,-lado/2,lado/2});
   v.push_back({-lado/2,-lado/2,lado/2});
   v.push_back({lado/2,-lado/2,lado/2});
   v.push_back({-lado/2,-lado/2,-lado/2});
   v.push_back({-lado/2,-lado/2,-lado/2});
   v.push_back({lado/2,-lado/2,-lado/2});

  /* this->setTextura("minecraft_dirt");
   ct.clear();
   // ABC
   ct.push_back({0.25, 1/3.0}); ct.push_back({0.25, 0.0}); ct.push_back({0.5, 0.0});
   // DEF
   ct.push_back({0.5, 1/3.0}); ct.push_back({0.5, 2/3.0}); ct.push_back({0.25, 2/3.0});
   // GHB
   ct.push_back({0.25, 1.0}); ct.push_back({0.5, 1.0}); ct.push_back({0.0, 1/3.0});
   // BCG
   ct.push_back({1.0, 1/3.0}); ct.push_back({0.75, 1/3.0});ct.push_back({0.0, 2/3.0});
   // GH
   ct.push_back({1.0, 2/3.0}); ct.push_back({0.75, 2/3.0});*/

}