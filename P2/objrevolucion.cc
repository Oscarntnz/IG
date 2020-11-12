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
   tapas.first = tapa_inf;
   tapas.second = tapa_sup;
   eje_rotacion = rotacion_eje;

   crearMalla(perfil, num_instancias, (tapas.first && tapas.second));

   escalar(20);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil_original, int num_instancias, EnumEjes rotacion_eje, bool tapa_sup, bool tapa_inf): tabla_c(0), tabla_v(0){
   tapas.first = tapa_inf;
   tapas.second = tapa_sup;
   eje_rotacion = rotacion_eje;

   crearMalla(perfil_original, num_instancias, (tapas.first && tapas.second));
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool conTapas){
   tipo_malla = TipoMalla::OBJREVO;
   
   Tupla3f v_actual = {0.0, 0.0, 0.0};
   Tupla3i c_actual = {0, 0, 0};
   float f_rotacion = 0;
   int a = 0, b = 0;

   perfil.assign(perfil_original.begin(), perfil_original.end());

   ordenarPuntos();
   crearPolos();

   M = perfil.size();
   N = num_instancias;

   // Añadir los vertices

   for(int i = 0; i < N; ++i){
      f_rotacion = (2*M_PI*i)/N;
      for(int j = 0; j < M; ++j){
            v_actual = calcularVectorRotado(j, f_rotacion);
            tabla_v.push_back(v_actual);
      }
   }

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

   // Añadir polos

   if(tapas.first)
      tabla_v.push_back(polo_i);
   if(tapas.second)
      tabla_v.push_back(polo_s);

   // Copiar las tablas a los vectores de vertices y caras

   for(auto it = tabla_v.begin(); it != tabla_v.end(); ++it)
      v.push_back(*it);

   for(auto it = tabla_c.begin(); it != tabla_c.end(); ++it){
      f.push_back(*it);
   }
   
   anadirTapas(tapas.first, tapas.second);

   rellenar_v_ajedrez();
   rellenar_v_colores();
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

void ObjRevolucion::anadirTapas(bool inferior, bool superior){
   int a = 0, b = 0;
   auto it = f.begin() + ((int)tabla_c.size() - 1);

   // tapa inferior
/*
  if(inferior)
      for (int i = 0; i < N; i++){
         a = M*i;
         b = M*((i + 1)%N);
         f.push_back({a, M*N, b});
      }

   // tapa superior
   if(superior)
      for (int i = 0; i < N; i++){
         a = M*(i + 1) - 1;
         b = (a + M)%(M*N);
         f.push_back({b, M*N + (tapas.first? 1 : 0), a});
      }
*/

   if(inferior){
      for (int i = 0; i < N; i++){
         a = M*i;
         b = M*((i + 1)%N);
         f.insert(it + i, {a, (int)v.size() - 2, b});
      }
      tapas.first = true;
   }

   // tapa superior
   if(superior){
      for (int i = 0; i < N; i++){
         a = M*(i + 1) - 1;
         b = (a + M)%(M*N);
         f.push_back({b, (int)v.size() - 1, a});
      }
      tapas.second = true;
   }

}

void ObjRevolucion::eliminarTapas(bool inferior, bool superior){
   int a = 0, b = 0;

   // tapa inferior
   // si queremos eliminar la inferior y esta en la tabla
   // la eliminamos

   if(inferior && tapas.first){
      auto it1 = f.begin() + ((int)tabla_c.size() - 1), it2 = (it1 + N);
      f.erase(it1, it2);
      tapas.first = false;
   }

   // tapa superior

   if(superior && tapas.second){
      for (int i = 0; i < N; i++)
         f.pop_back();
      
      tapas.second = false;
   }
}

void ObjRevolucion::crearPerfilDebug(){
   for(auto it = perfil.begin(); it != perfil.end(); ++it)
        v.push_back(*it);
   
   if(v.size() > 2)
    for(int i = 0; i < (int)v.size() - 2; i++)
        f.push_back({i%(int)v.size(),(i+1)%(int)v.size(),(i+2)%(int)v.size()});
   else
      f.push_back({0,1,2});
}

void ObjRevolucion::toggleTapas(bool inferior, bool superior){
   if(inferior){
      if(tapas.first)
         eliminarTapas(true, false);
      else
         anadirTapas(true, false);
   }

   if(superior){
      if(tapas.second)
         eliminarTapas(false, true);
      else
         anadirTapas(false, true);
   }

   rellenar_v_ajedrez();

}

void ObjRevolucion::crearPolos(){
   std::pair<bool,bool> los_tiene = std::make_pair(false, false);
   EnumEjes eje_nulo, eje_nulo_2;

   if(eje_rotacion == EnumEjes::E_X){
      eje_nulo = EnumEjes::E_Y;
      eje_nulo_2 = EnumEjes::E_Z;
   }
   else if(eje_rotacion == EnumEjes::E_Y){
      eje_nulo = EnumEjes::E_X;
      eje_nulo_2 = EnumEjes::E_Z;
   }
   else{
      eje_nulo = EnumEjes::E_X;
      eje_nulo_2 = EnumEjes::E_Y;
   }

   if(perfil.front()(eje_nulo) == 0 && perfil.front()(eje_nulo_2) == 0)
      los_tiene.first = true;
   if(perfil.back()(eje_nulo) == 0 && perfil.front()(eje_nulo_2) == 0)
      los_tiene.second = true;

   if(!los_tiene.first){
      polo_i = perfil.front();
      polo_i(eje_nulo) = 0;
      polo_i(eje_nulo_2) = 0;
   }
   else
      perfil.erase(perfil.begin());
   

   if(!los_tiene.second){
      polo_s = perfil.back();
      polo_s(eje_nulo) = 0;
      polo_s(eje_nulo_2) = 0;
   }
   else
      perfil.pop_back();

}