#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include <cmath>
#include <limits>


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias,
EnumEjes rotacion_eje, bool tapa_sup, bool tapa_inf, bool con_tapas): tabla_c(0), tabla_v(0){
   ply::read_vertices(archivo, perfil);
   eje_rotacion = rotacion_eje;
   tiene_tapas.first = tapa_inf;
   tiene_tapas.second = tapa_sup;
   
   int instancias_perf = num_instancias;
   if(instancias_perf < 2) instancias_perf = 2;

   //crearPerfilDebug();
   crearMalla(perfil, instancias_perf, con_tapas);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> perfil_original, int num_instancias,
EnumEjes rotacion_eje, bool tapa_sup, bool tapa_inf, bool con_tapas): tabla_c(0), tabla_v(0){
   eje_rotacion = rotacion_eje;
   tiene_tapas.first = tapa_inf;
   tiene_tapas.second = tapa_sup;

   int instancias_perf = num_instancias;
   if(instancias_perf < 2) instancias_perf = 2;

   crearMalla(perfil_original, instancias_perf, con_tapas);
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool conTapas){
   tipo_malla = TipoMalla::OBJREVO;
   tapas = false;
   
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

   for(int i = 0; i < N + 1; ++i){
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
         b = M*(i + 1) + j;
         c_actual = {a, b, b + 1};
         tabla_c.push_back(c_actual);
         c_actual = {a, b + 1, a + 1};
         tabla_c.push_back(c_actual);
      }
   }

   // Copiar las tablas a los vectores de vertices y caras

   for(auto it = tabla_v.begin(); it != tabla_v.end(); ++it)
      v.push_back(*it);

   for(auto it = tabla_c.begin(); it != tabla_c.end(); ++it){
      f.push_back(*it);
   }

   tam_sin_tapas = f.size();

   // Añadir polos y tapas

   v.push_back(polo_i);
   v.push_back(polo_s);

   anadirTapas();

   if(conTapas)
      tam_en_uso = tam_con_tapas;
   else
      tam_en_uso = tam_sin_tapas;

   tapas = conTapas;

   rellenar_vectores();
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

void ObjRevolucion::anadirTapas(){
   int a = 0, b = 0, c;

   // tapa inferior

   if(tiene_tapas.first){
      c = M*(N+1);
      for (int i = 0; i < N + 1; i++){
         a = M*i;
         b = (a + M)%(M*(N+1));
         f.push_back({a, c, b});
      }
   }

   // tapa superior

   if(tiene_tapas.second){
      c = M*(N+1) + 1;
      for (int i = 0; i < N + 1; i++){
         a = M*(i + 1) - 1;
         b = (a + M)%(M*(N+1));
         f.push_back({b, c, a});
      }
   }

   tam_con_tapas = f.size();
}

void ObjRevolucion::crearPerfilDebug(){
   std::pair<bool,bool> los_tiene;

   crearPolos();

   perfil.insert(perfil.begin(), polo_i);
   perfil.push_back(polo_s);

   for(auto it = perfil.begin(); it != perfil.end(); ++it)
        v.push_back(*it);
   
   if(v.size() > 2)
    for(int i = 0; i < (int)v.size() - 2; i++)
        f.push_back({i%(int)v.size(),(i+1)%(int)v.size(),(i+2)%(int)v.size()});
   else
      f.push_back({0,1,2});

   rellenar_v_colores();
}

void ObjRevolucion::toggleTapas(){
   if(tapas)
      tam_en_uso = tam_sin_tapas;
   else
      tam_en_uso = tam_con_tapas;

   tapas = !tapas;
}

std::pair<bool,bool> ObjRevolucion::crearPolos(){
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

   polo_i = perfil.front();
   polo_s = perfil.back();

   if(fabs(polo_i(eje_nulo)) < std::numeric_limits<float>::epsilon() &&
   fabs(polo_i(eje_nulo_2)) < std::numeric_limits<float>::epsilon())
      los_tiene.first = true;
   if(fabs(polo_s(eje_nulo)) < std::numeric_limits<float>::epsilon() &&
   fabs(polo_s(eje_nulo_2)) < std::numeric_limits<float>::epsilon())
      los_tiene.second = true;

   // Si no los tiene, creamos la proyeccion sobre el eje en el que rota

   if(!los_tiene.first){
      polo_i(eje_nulo) = 0;
      polo_i(eje_nulo_2) = 0;
   }
   else if(tiene_tapas.first)
      perfil.erase(perfil.begin());
   

   if(!los_tiene.second){
      polo_s(eje_nulo) = 0;
      polo_s(eje_nulo_2) = 0;
   }
   else if(tiene_tapas.second)
      perfil.pop_back();

   return(los_tiene);
}

void ObjRevolucion::calcularPuntosTex(){
   std::vector<float> tabla_d(M, 0.0);
   float si, dj = 0, pj,
   x = 0.0, y = 0.0, z = 0.0;
   ct.clear();

   for(int i = 1; i < M; ++i){
      x = perfil[i](EnumEjes::E_X) - perfil[i - 1](EnumEjes::E_X);
      y = perfil[i](EnumEjes::E_Y) - perfil[i - 1](EnumEjes::E_Y);
      z = perfil[i](EnumEjes::E_Z) - perfil[i - 1](EnumEjes::E_Z);
      pj = sqrt(x*x + y*y + z*z);
      tabla_d[i] = tabla_d[i - 1] + pj;
   }

   for(auto it = tabla_d.begin(); it != tabla_d.end(); ++it)
      *it = 1-(*it/(*(--tabla_d.end())));

   for(int i = 0; i < N + 1; ++i){
      si = (float)i/N;
      for(int j = 0; j < M; ++j){
         ct.push_back({si, tabla_d[j]});
      }
   }
   
   ct.push_back({0.5, 1.0});
   ct.push_back({0.5, 0.0});
}