#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   reserva_espacio(8,12);

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

   rellenar_v_colores();
}

