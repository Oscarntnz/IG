#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   v.resize(8);
   f.resize(12);
   a.resize(f.size()/2);
   a_2.resize(f.size()/2);
   c_i.resize(v.size());
   c_d.resize(v.size());
   c_p.resize(v.size());
   c_l.resize(3*f.size());
   c_a.resize(3*v.size()/2);
   c_a_2.resize(3*v.size()/2);

   // inicializar la tabla de vértices

   v[0]={-lado/2,lado/2,lado/2}; v[1]={-lado/2,-lado/2,lado/2}; v[2]={lado/2,-lado/2,lado/2};
   v[3]={lado/2,lado/2,lado/2}; v[4]={lado/2,lado/2,-lado/2}; v[5]={-lado/2,lado/2,-lado/2};
   v[6]={-lado/2,-lado/2,-lado/2}; v[7]={lado/2,-lado/2,-lado/2};

   // inicializar la tabla de caras o triángulos:

   //Frontal
   f[0]={2,0,1}; f[1]={2,3,0};
   //Derecha
   f[2]={3,2,7}; f[3]={3,7,4}; 
   //Trasera
   f[4]={6,4,7}; f[5]={6,5,4};
   //Izquierda
   f[6]={5,6,1}; f[7]={5,1,0};
   //Inferior
   f[8]={1,6,7}; f[9]={1,7,2};
   //Superior
   f[10]={5,0,3}; f[11]={5,3,4};

   //Inicializacion de las tablas para el modo ajedrez

   unsigned int j = 0, k = 0;
   for(unsigned int i = 0; i < f.size(); i++){
      if(i%2 == 0){
         a[j] = f[i];
         j++;
      }
      else{
         a_2[k] = f[i];
         k++;
      }
   }

   //Inicializacion de los vectores de colores

   std::fill(c_i.begin(), c_i.end(), color_i);
   std::fill(c_d.begin(), c_d.end(), color_d);
   std::fill(c_p.begin(), c_p.end(), color_lineas);
   std::fill(c_l.begin(), c_l.end(), color_puntos);

   for(auto it = c_a.begin(); it != c_a.end(); ++it)
      *it = color_ajedrez_1;
   for(auto it = c_a_2.begin(); it != c_a_2.end(); ++it)
      *it = color_ajedrez_2;

}

