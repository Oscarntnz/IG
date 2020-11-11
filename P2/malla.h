// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

enum ModoDibujado{INMEDIATO, DIFERIDO, NINGUNO};
enum ModoVisualizacion : unsigned int {PUNTOS = 0, LINEAS = 1, SOLIDO = 2, AJEDREZ = 3};

class Malla3D
{
   public:
   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato();

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw();

   inline void toggle_visibility(){    //Cambiar visibilidad
      visible = !visible;
   }
   inline const bool get_visibility(){       //true = visible, false = invisible
      return visible;
   }

   inline void cambiar_dibujado(ModoDibujado modo){
      if(modo_dibujo != modo)
         modo_dibujo = modo;
   }

   void cambiar_visualizacion(ModoVisualizacion modo);
   void mover(Tupla3f vector_despl);      //Mueve los vertices sumando los componentes del parametro
   void escalar(float factor);

   private:

   // atributos privados

   GLuint id_vbo_ver = 0,        // id de VBO de vertices
   id_vbo_tri = 0,               // id de VBO de triangulos
   id_vbo_col = 0,               // id de VBO de colores
   id_vbo_aj1 = 0,               // id de VBO de mitad de los triangulos ajedrez
   id_vbo_aj2 = 0,               // id de VBO de otra mitad de los triangulos ajedrez
   id_vbo_pun = 0,               // id de VBO de color de puntos
   id_vbo_lin = 0,               // id de VBO de color de lineas
   id_vbo_ca1 = 0,               // id de VBO de color de ajedrez 1
   id_vbo_ca2 = 0;               // id de VBO de color de ajedrez 2

   bool visible = false;         // bool para hacer visible o invisible la malla
   ModoDibujado modo_dibujo = ModoDibujado::INMEDIATO; // modo de dibjudado de la malla
   static const unsigned int N_MODOS_V = 4;             // nº de modos de visualizacion
   bool modos_visualizacion[N_MODOS_V] = {false, false, true, false}; // vector de bool para saber el tipo de visualizacion

   // funciones privadas

   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);
   void dibuja(std::vector<Tupla3i> v);
   void dibuja_dif(std::vector<Tupla3i> v, GLuint id);

   protected:

   void calcular_normales() ;       // calcula tabla de normales de vértices (práctica 3)
   void rellenar_v_colores();       // rellena el vector de colores
   void rellenar_v_ajedrez();       // rellena el vector de caras del modo ajedrez
   void reserva_espacio(unsigned int vertices, unsigned int caras);  // reserva espacio en todos los vectores
   void reserva_espacio(); // reserva espacio en todos los vectores una vez ya tenemos v y f


   // vectores de vertices
   std::vector<Tupla3f> v;          // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)

   // vectores de triangulos
   std::vector<Tupla3i> f;          // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> a;          // una terna de 3 enteros por la mitad de las caras o triángulos del modo ajedrez
   std::vector<Tupla3i> a_2;        // una terna de 3 enteros por la otra mitad de las caras o triángulos del modo ajedrez

   // vectores de colores
   std::vector<Tupla3f> c_i;        // tabla de colores para modo inmediato
   std::vector<Tupla3f> c_d;        // tabla de colores para modo diferido
   std::vector<Tupla3f> c_p;        // tabla de colores para visualizacion puntos
   std::vector<Tupla3f> c_l;        // tabla de colores para visualizacion lineas
   std::vector<Tupla3f> c_a;        // tabla de colores para los triangulos negros visualizacion ajedrez
   std::vector<Tupla3f> c_a_2;      // tabla de colores para los triangulos blancos visualizacion ajedrez

   Tupla3f color_i = {1.0,0.0,1.0};                // color modo inmediato
   Tupla3f color_d = {0.0,1.0,1.0};                // color modo diferido
   const Tupla3f color_puntos = {0.0,0.0,1.0};     // color de los puntos (azules)
   const Tupla3f color_lineas = {1.0,0.0,0.0};     // color de las lineas (rojas)
   const Tupla3f color_ajedrez_1 = {1.0,1.0,0.0};  // primer color modo ajedrez
   const Tupla3f color_ajedrez_2 = {0.0,0.0,0.0};  // segundo color modo ajedrez

} ;


#endif
