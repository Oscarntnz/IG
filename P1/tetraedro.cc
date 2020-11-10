#include "aux.h"
#include "malla.h"
#include "tetraedro.h"
#include "cmath"
#include <iostream>

Tetraedro::Tetraedro(float lado)
{
   float altura_caras = 0.0,
   altura_tetraedro = 0.0,
   distancia_gravicentro = lado*sqrt(3)/6; //Distanica entre el punto intermedio 
                                          //de uno de los lados de la base al gravicentro
                                          // D(AB/2-G) = D(AB)*sqrt(3)/6 siendo AB dos puntos de la base

   v.resize(4);
   f.resize(4);
   a.resize(f.size()/2);
   a_2.resize(f.size()/2);
   c_i.resize(v.size());
   c_d.resize(v.size());
   c_p.resize(v.size());
   c_l.resize(3*f.size());
   c_a.resize(3*v.size()/2);
   c_a_2.resize(3*v.size()/2);

   //Pitagoras con lado como hipotenusa y distancia al punto intermedio de la base como cateto opuesto
   // para calcular la altura de las caras
   altura_caras = sqrt(lado*lado - (lado/2)*(lado/2));

   //Pitagoras con el ldibujarN_MODOS_Vado como hipotenusa y la distancia al gravicentro como cateto opuesto
   altura_tetraedro = sqrt(lado*lado - distancia_gravicentro*distancia_gravicentro);
    
   // inicializar la tabla de vértices

   v[0]={0,altura_tetraedro/2,0}; v[1]={-lado/2,-altura_tetraedro/2,-distancia_gravicentro};
   v[2]={0,-altura_tetraedro/2,altura_caras-distancia_gravicentro}; v[3]={lado/2,-altura_tetraedro/2,-distancia_gravicentro};

   // inicializar la tabla de caras o triángulos:

   f[0]={0,1,2}; f[1]={0,2,3}; f[2]={0,3,1};
   f[3]={2,1,3};

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

