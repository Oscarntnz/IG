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
#include "cuadro.h"
#include "brazo.h"
#include "pierna.h"
#include "cabeza.h"
#include "krillin.h"
#include <climits>

typedef enum {NADA, SELOBJETO, SELVISUALIZACION, SELDIBUJADO, SELILUMINACION, VARALPHA, VARBETA, SELGLIB} menu;

class Escena
{

   private:

    //Variables

    MenuCtl menu_ctl;
    bool debug = false;
    bool coloresAleatorios = false;
    unsigned int gLib = UINT_MAX;
    bool animar = true;
    std::vector<float> velocAnimacion;

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
    void modifGLib(int grado, bool aumentar);
    void modifVeloc(float factor);

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
   Cuadro * cuadro = nullptr;
   ObjRevolucion * lata = nullptr;
   Krillin * krillin = nullptr;
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

    // Animacion

    void animarModeloJerarquico();
};
#endif
