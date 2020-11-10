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

   reserva_espacio(4,4);

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

   // Inicializacion de las tablas para el modo ajedrez

   // Inicializacion de los vectores de colores

   rellenar_v_colores();

}

