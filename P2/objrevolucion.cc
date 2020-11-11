#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include <cmath>



// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, EnumEjes rotacion_eje, bool tapa_sup, bool tapa_inf): tabla_c(0), tabla_v(0){
   ply::read_vertices(archivo, perfil);
   tapas.first = tapa_sup;
   tapas.second = tapa_inf;
   eje_rotacion = rotacion_eje;

   crearMalla(perfil, num_instancias);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil_original, int num_instancias, EnumEjes rotacion_eje, bool tapa_sup, bool tapa_inf): tabla_c(0), tabla_v(0){
   perfil.assign(perfil_original.begin(), perfil_original.end());
   tapas.first = tapa_sup;
   tapas.second = tapa_inf;
   eje_rotacion = rotacion_eje;

   crearMalla(perfil_original, num_instancias);
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias){
   Tupla3f v_actual = {0.0, 0.0, 0.0};
   Tupla3i c_actual = {0, 0, 0};
   float f_rotacion = 0;
   int a = 0, b = 0;

   M = perfil_original.size();
   N = num_instancias;

   ordenarPuntos();
   eliminarPolos();

   // Añadir los vertices

   for(int i = 0; i < N; ++i){
      f_rotacion = (2*M_PI*i)/N;
      for(int j = 0; j < M; ++j){
            v_actual = calcularVectorRotado(j, f_rotacion);
            tabla_v.push_back(v_actual);
      }
   }

   // Añadir polos

   if(tapas.second)
      tabla_v.push_back(polo_i);
   if(tapas.first)
      tabla_v.push_back(polo_s);

   // Añadir caras

   for(int i = 0; i < N; ++i){
      for(int j = 0; j < M - 1; ++j){
         a = M*i + j;
         b = M*((i + 1)%N) + j;
         c_actual = {a, b, b + 1};
         tabla_c.push_back(c_actual);
         c_actual = {a, b + 1, a + 1};
         tabla_c.push_back(c_actual);
      }
   }

   for(auto it = tabla_v.begin(); it != tabla_v.end(); ++it)
      v.push_back(*it);

   for(auto it = tabla_c.begin(); it != tabla_c.end(); ++it){
      f.push_back(*it);
   }
   
   anadirTapas();

}

void ObjRevolucion::ordenarPuntos(){
   std::vector<Tupla3f> auxiliar(perfil.size());
   int i = 0;

   if(perfil.front()(eje_rotacion) > perfil.back()(eje_rotacion)){
      for(auto it = perfil.rbegin(); it != perfil.rend(); ++it, ++i)
         auxiliar[i] = *it;
      perfil.swap(auxiliar);
   }
}

void ObjRevolucion::eliminarPolos(){

   if(tapas.first){
         polo_s = perfil.back();
         perfil.pop_back();
      
   }
   if(tapas.second){
      polo_i = perfil.front();
      perfil.erase(perfil.begin());
   } 
}

Tupla3f ObjRevolucion::calcularVectorRotado(int j, float factor_rotacion){
   Tupla3f salida = {0.0, 0.0, 0.0};

   if(eje_rotacion == EnumEjes::E_X){
      salida(EnumEjes::E_X) = perfil[j](EnumEjes::E_X);
      salida(EnumEjes::E_Y) = perfil[j](EnumEjes::E_Y)*cos(factor_rotacion) + perfil[j](EnumEjes::E_Z)*-sin(factor_rotacion);
      salida(EnumEjes::E_Z) = perfil[j](EnumEjes::E_Y)*sin(factor_rotacion) + perfil[j](EnumEjes::E_Z)*cos(factor_rotacion);
   }
   else if(eje_rotacion == EnumEjes::E_Y){
      salida(EnumEjes::E_X) = perfil[j](EnumEjes::E_X)*cos(factor_rotacion) + perfil[j](EnumEjes::E_Z)*sin(factor_rotacion);
      salida(EnumEjes::E_Y) = perfil[j](EnumEjes::E_Y);
      salida(EnumEjes::E_Z) = perfil[j](EnumEjes::E_X)*-sin(factor_rotacion) + perfil[j](EnumEjes::E_Z)*cos(factor_rotacion);
   }
   else{
      salida(EnumEjes::E_X) = perfil[j](EnumEjes::E_X)*cos(factor_rotacion) + perfil[j](EnumEjes::E_Y)*-sin(factor_rotacion);
      salida(EnumEjes::E_Y) = perfil[j](EnumEjes::E_X)*sin(factor_rotacion) + perfil[j](EnumEjes::E_Y)*cos(factor_rotacion);
      salida(EnumEjes::E_Z) = perfil[j](EnumEjes::E_Z);
   }

   return salida;
}

void ObjRevolucion::anadirTapas(){
   int a = 0, b = 0;

   // tapa superior

   if(tapas.first)
      for (int i = 0; i < N; i++){
         a = M*(i + 1) - 1;
         b = a + N;
         f.push_back({a, M*N + 1, b});
      }   

   // tapa inferior

   if(tapas.second)
      for (int i = 0; i < N; i++){
         a = M*i;
         b = M*((i + 1)%N);
         f.push_back({a, M*N, b});
      }


}