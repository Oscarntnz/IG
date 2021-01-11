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
#include "material.h"
#include "textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

enum ModoDibujado{INMEDIATO, DIFERIDO, NINGUNO};
enum ModoVisualizacion : unsigned int {PUNTOS = 0, LINEAS = 1, SOLIDO = 2, AJEDREZ = 3, ILUMINACION = 4};
enum TipoMalla{ESTANDAR, OBJREVO, OBJPLY};

class Malla3D
{
   public:

   virtual ~Malla3D();

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(bool modoSeleccion = false);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(bool modoSeleccion = false);

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw(bool modoSeleccion = false);

   void setColor(Tupla3f inmediato = color_i, Tupla3f diferido = color_d);

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

   inline TipoMalla getTipoMalla(){
      return tipo_malla;
   }

   void cambiar_visualizacion(ModoVisualizacion modo);
   void mover(Tupla3f vector_despl);      //Mueve los vertices sumando los componentes del parametro

   inline void setMaterial(Material mat){
      m = mat;
   }

   inline GLenum toggleShadeMode(){
      if(sMode == GL_SMOOTH)
         sMode = GL_FLAT;
      else
         sMode = GL_SMOOTH;

      return sMode;
   }

   inline void setSeleccionado(bool valor){
      seleccionado = valor;
   }

   inline const bool getSeleccionado()const{
      return seleccionado;
   }

   void setTextura(std::string archivo);
   void setColorModoSelec(Tupla3f color);

   inline Tupla3f getColorModoSelec(){
      return c_m_selec.front();
   }

   inline bool getSeleccionable(){
      return seleccionable;
   }

   inline void setSeleccionable(bool seleccionable){
      this->seleccionable = seleccionable;
   }

   private:

   // funciones privadas

   GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);
   void dibuja(const std::vector<Tupla3i> & vect, size_t tam);
   void dibuja_dif(const std::vector<Tupla3i> & vect, GLuint id, size_t tam);
   void reserva_espacio(); // reserva espacio en todos los vectores una vez ya tenemos v y f
   void calculaTablaNormales();
   virtual void calcularPuntosTex();

   inline virtual const size_t getTamVCaras()const{
      return f.size();
   }
   
   inline const Tupla3f getColorSolido(){
      if(seleccionado)
         return c_selec.front();
      else
         if(modo_dibujo == ModoDibujado::DIFERIDO)
               return c_d.front();
            else
               return c_i.front();
   }

   // atributos privados

   Material m;
   GLenum sMode = GL_SMOOTH;       // modo de sombreado
   const int N_VBO = 9;
   GLuint id_vbo_ver = 0,        // id de VBO de vertices
   id_vbo_tri = 0,               // id de VBO de triangulos
   id_vbo_col = 0,               // id de VBO de colores
   id_vbo_aj1 = 0,               // id de VBO de mitad de los triangulos ajedrez
   id_vbo_aj2 = 0,               // id de VBO de otra mitad de los triangulos ajedrez
   id_vbo_pun = 0,               // id de VBO de color de puntos
   id_vbo_lin = 0,               // id de VBO de color de lineas
   id_vbo_ca1 = 0,               // id de VBO de color de ajedrez 1
   id_vbo_ca2 = 0,               // id de VBO de color de ajedrez 2
   id_vbo_nv = 0,                // id de VBO del vector de normales
   id_vbo_selec = 0,             // id de VBO del color cuando se seleccione el objeto
   id_vbo_m_selec = 0;           // id de VBO del vector de color cuando se dibuje el modo seleccion

   bool visible = true;         // bool para hacer visible o invisible la malla
   bool seleccionado = false;
   bool seleccionable = true;
   ModoDibujado modo_dibujo = ModoDibujado::DIFERIDO; // modo de dibjudado de la malla
   static const unsigned int N_MODOS_V = 5;             // nº de modos de visualizacion
   bool modos_visualizacion[N_MODOS_V] = {false, false, false, false, true};

   protected:

   void calcular_normales() ;       // calcula tabla de normales de vértices (práctica 3)
   void rellenar_v_colores();       // rellena el vector de colores
   void rellenar_v_ajedrez();       // rellena el vector de caras del modo ajedrez
   void rellenar_vectores();
   void elimina_vbo();

   inline bool tieneTextura(){
      return textura != nullptr && !ct.empty();
   }


   // vectores de vertices
   std::vector<Tupla3f> v;          // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)

   // vectores de triangulos
   std::vector<Tupla3i> f;          // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> a;          // una terna de 3 enteros por la mitad de las caras o triángulos del modo ajedrez
   std::vector<Tupla3i> a_2;        // una terna de 3 enteros por la otra mitad de las caras o triángulos del modo ajedrez

   // vectores de normales
   std::vector<Tupla3f> nv;

   // vectores de colores
   std::vector<Tupla3f> c_i;        // tabla de colores para modo inmediato
   std::vector<Tupla3f> c_d;        // tabla de colores para modo diferido
   std::vector<Tupla3f> c_p;        // tabla de colores para visualizacion puntos
   std::vector<Tupla3f> c_l;        // tabla de colores para visualizacion lineas
   std::vector<Tupla3f> c_a;        // tabla de colores para los triangulos negros visualizacion ajedrez
   std::vector<Tupla3f> c_a_2;      // tabla de colores para los triangulos blancos visualizacion ajedrez
   std::vector<Tupla3f> c_selec;      // tabla de colores para cuando la malla esté seleccionada
   std::vector<Tupla3f> c_m_selec;

   static const Tupla3f color_i;          // color modo inmediato
   static const Tupla3f color_d;          // color modo diferido
   static const Tupla3f color_puntos;     // color de los puntos (azules)
   static const Tupla3f color_lineas;     // color de las lineas (rojas)
   static const Tupla3f color_ajedrez_1;  // primer color modo ajedrez
   static const Tupla3f color_ajedrez_2;  // segundo color modo ajedrez
   static const Tupla3f color_seleccionado;  // color al ser seleccionado
   static const Tupla3f color_modo_seleccion;  // color en modo seleccion

   TipoMalla tipo_malla = TipoMalla::ESTANDAR;

   Textura * textura = nullptr ;
   std::vector<Tupla2f>ct;          // tabla de coordenadas de texturas
} ;


#endif
