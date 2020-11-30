#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "menuctl.h"
#include "cono.h"
#include "cilindro.h"
#include "esfera.h"
#include "luzdireccional.h"
#include "luzposicional.h"

typedef enum {NADA, SELOBJETO, SELVISUALIZACION, SELDIBUJADO, SELILUMINACION, VARALPHA, VARBETA} menu;

class Escena
{

   private:

    //Variables

    enum Objetos {CUBO = 0, TETRAEDRO = 1, PLY = 2, CILINDRO = 3, CONO = 4, ESFERA = 5, REVO = 6, NULO};
    Objetos objeto_a_dibujar;
    MenuCtl menu_ctl;
    bool debug = false;

    //Funciones
    
    void cambiar_dibujado(ModoDibujado modo);
    void cambiar_visualizacion(ModoVisualizacion modo);
    void cambiaTapas();
    void ajustar_objeto(int i);
    GLenum toggle_sombreado();
    float randomFloat();
    Tupla3f randomColor();
    void dibuja_objetos();
    void dibuja_luces();

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)
       
       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();


   void clear_window();

   menu modoMenu = NADA;
   // Objetos de la escena
   std::vector<Malla3D *> objetos_escena;
   Ejes ejes;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro = nullptr ; // es importante inicializarlo a 'nullptr'
   ObjPLY * objply = nullptr;
   Cono * cono = nullptr;
   Cilindro * cilindro = nullptr;
   Esfera * esfera = nullptr;
   ObjRevolucion * objrevo = nullptr;
   ObjRevolucion * objrevo2 = nullptr;
   std::vector<Luz *> luces;

   // Posiciones
   std::vector<Tupla3f> pos_objetos;
   // Escalas
   std::vector<Tupla3f> escalas_objetos;

   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar();

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
