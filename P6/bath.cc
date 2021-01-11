#include "aux.h"
#include "malla.h"
#include "bath.h"
#include "cubo.h"

Bath::Bath(float lado)
{
   v.clear();
   f.clear();

   // ABC
   v.push_back({-lado/2,lado/2,lado/2}); v.push_back({-lado/2,-lado/2,lado/2}); v.push_back({lado/2,-lado/2,lado/2});
   // DEF
   v.push_back({lado/2,lado/2,lado/2}); v.push_back({lado/2,lado/2,-lado/2}); v.push_back({-lado/2,lado/2,-lado/2});
   // GH
   v.push_back({-lado/2,-lado/2,-lado/2}); v.push_back({lado/2,-lado/2,-lado/2});

   // A2 A3 D2 E2 F2 F3
   v.push_back({-lado/2,lado/2,lado/2});
   v.push_back({-lado/2,lado/2,lado/2});
   v.push_back({lado/2,lado/2,lado/2});
   v.push_back({lado/2,lado/2,-lado/2});
   v.push_back({-lado/2,lado/2,-lado/2});
   v.push_back({-lado/2,lado/2,-lado/2});

   f.push_back({0,6,5}); f.push_back({0,1,6});
   f.push_back({1,7,6}); f.push_back({1,2,7}); 
   f.push_back({8,2,1}); f.push_back({8,10,2});
   f.push_back({6,11,12}); f.push_back({6,7,11});
   f.push_back({2,4,7}); f.push_back({2,3,4});
   f.push_back({3,13,4}); f.push_back({3,9,13});

   rellenar_vectores();

   this->setTextura("cubemap bath");
   ct.clear();
   // ABC
   ct.push_back({0.0, 1/3.0}); ct.push_back({0.25, 1/3.0}); ct.push_back({0.5, 1/3.0});
   // DEF
   ct.push_back({0.75, 1/3.0}); ct.push_back({0.75, 2/3.0}); ct.push_back({0.0, 2/3.0});
   // G H A2
   ct.push_back({0.25, 2/3.0}); ct.push_back({0.5, 2/3.0}); ct.push_back({0.25, 0.0});
   // A3 D2 E2
   ct.push_back({1.0, 1/3.0}); ct.push_back({0.5, 0.0}); ct.push_back({0.5, 1.0});
   // F2 F3
   ct.push_back({0.25, 1.0}); ct.push_back({1.0, 2/3.0});

}

