#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;
    objeto_a_dibujar = Objetos::NINGUNO;

    ejes.changeAxisSize(5000);

    // crear los objetos de la escena
    
    cubo = new Cubo(100);
    tetraedro = new Tetraedro(100);

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

   glEnable(GL_CULL_FACE);

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
   ejes.draw();
    //   Dibujar los diferentes elementos de la escena
    // Habrá que tener en esta primera práctica una variable que indique qué objeto se ha de visualizar
    // y hacer 
    // cubo.draw()
    // o
    // tetraedro.draw()

   if(objeto_a_dibujar == Objetos::CUBO || cubo->get_visibility()){
      cubo->draw();
      objeto_a_dibujar == Objetos::NINGUNO;
   }
   if(objeto_a_dibujar == Objetos::TETRAEDRO || tetraedro->get_visibility()){
      tetraedro->draw();
      objeto_a_dibujar == Objetos::NINGUNO;
   }
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir=false;
   switch( toupper(tecla) )
   {
      case 'Q' :
         if (modoMenu!=NADA)
            modoMenu=NADA;            
         else {
            salir=true ;
         }
         break ;
      case 'O' :
         // ESTAMOS EN MODO SELECCION DE OBJETO
         if(modoMenu==NADA && modoMenu!=SELOBJETO){
            modoMenu=SELOBJETO;
            std::cout << "Modo de selleccion de objeto" << std::endl;
         }
         else
            std::cout << "Opcion no valida" << std::endl;

         break ;

      // OPCIONES DE SELECCION DE OBJETO
      
      case 'C' :
         // ESTAMOS SELECCIONANDO EL CUBO
         if(modoMenu == SELOBJETO){
            if(!cubo->get_visibility()){
               objeto_a_dibujar = Objetos::CUBO;
               cubo->toggle_visibility();
            }
            else{
               cubo->toggle_visibility();
               objeto_a_dibujar = Objetos::NINGUNO;
            }
            std::cout << "Seleccionado cubo," << " visibilidad = " << (cubo->get_visibility()? "visible" : "invisible") << std::endl;
            modoMenu = NADA;
         }
         else
            std::cout << "Opcion no valida" << std::endl;

         break ;
      case 'T' :
         // ESTAMOS SELECCIONANDO EL TETRAEDRO
         if(modoMenu==SELOBJETO){
            if(!tetraedro->get_visibility()){
               objeto_a_dibujar = Objetos::TETRAEDRO;
               tetraedro->toggle_visibility();
            }
            else{
               tetraedro->toggle_visibility();
               objeto_a_dibujar = Objetos::NINGUNO;
            }
            std::cout << "Seleccionado tetraedro," << " visibilidad = " << (tetraedro->get_visibility()? "visible" : "invisible") << std::endl;
            modoMenu = NADA;
         }
         else
            std::cout << "Opcion no valida" << std::endl;

         break ;

      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         if (modoMenu==NADA && modoMenu!=SELVISUALIZACION){
            modoMenu=SELVISUALIZACION;
            std::cout << "Modo de selleccion de visualizacion" << std::endl;
         }
         else
            std::cout << "Opcion no valida" << std::endl;

         break ;
      
      // OPCIONES DE SELECCION DE VISUALIZACION

      case 'P' :
         // ESTAMOS SELECCIONANDO MODO DE VISUALIZACION LINEAS
         if (modoMenu==SELVISUALIZACION){
            cambiar_visualizacion(ModoVisualizacion::PUNTOS);
            std::cout << "Modo de visualizacion puntos cambiado" << std::endl;
            modoMenu=NADA;
         }
         else
            std::cout << "Opcion no valida" << std::endl;
         
         break;

      case 'L' :
         // ESTAMOS SELECCIONANDO MODO DE VISUALIZACION LINEAS
         if (modoMenu==SELVISUALIZACION){
            cambiar_visualizacion(ModoVisualizacion::LINEAS);
            std::cout << "Modo de visualizacion lineas cambiado" << std::endl;
            modoMenu=NADA;
         }
         else
            std::cout << "Opcion no valida" << std::endl;
         
         break;

      case 'S' :
         // ESTAMOS SELECCIONANDO MODO DE VISUALIZACION SOLIDO
         if (modoMenu==SELVISUALIZACION){
            cambiar_visualizacion(ModoVisualizacion::SOLIDO);
            std::cout << "Modo de visualizacion solido cambiado" << std::endl;
            modoMenu=NADA;
         }
         else
            std::cout << "Opcion no valida" << std::endl;
         
         break;

      case 'A' :
         // ESTAMOS SELECCIONANDO MODO DE VISUALIZACION AJEDREZ
         if (modoMenu==SELVISUALIZACION){
            cambiar_visualizacion(ModoVisualizacion::AJEDREZ);
            std::cout << "Modo de visualizacion ajedrez cambiado" << std::endl;
            modoMenu=NADA;
         }
         else
            std::cout << "Opcion no valida" << std::endl;
         
         break;

      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         if (modoMenu==NADA && modoMenu!=SELDIBUJADO){
            modoMenu=SELDIBUJADO;
            std::cout << "Modo de selleccion de dibujado" << std::endl;
         }
         else
            std::cout << "Opcion no valida" << std::endl;

         break;
      
      // OPCIONES DE SELECCION DE DIBUJADO
      
      case '1' :
         // ESTAMOS SELECCIONANDO MODO DE DIBUJADO INMEDIATO
         if (modoMenu==SELDIBUJADO){
            cambiar_dibujado(ModoDibujado::INMEDIATO);
            std::cout << "Modo de dibujado inmediato" << std::endl;
            modoMenu=NADA;
         }
         else
            std::cout << "Opcion no valida" << std::endl;
         
         break;
      case '2' :
         // ESTAMOS SELECCIONANDO MODO DE DIBUJADO DIFERIDO
         if (modoMenu==SELDIBUJADO){
            cambiar_dibujado(ModoDibujado::DIFERIDO);
            std::cout << "Modo de dibujado diferido" << std::endl;
            modoMenu=NADA;
         }
         else
            std::cout << "Opcion no valida" << std::endl;
         
         break;
      default:
         std::cout << "Opcion no valida" << std::endl;
   }
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}

void Escena::cambiar_dibujado(ModoDibujado modo){
   cubo->cambiar_dibujado(modo);
   tetraedro->cambiar_dibujado(modo);
}

void Escena::cambiar_visualizacion(ModoVisualizacion modo){
   cubo->cambiar_visualizacion(modo);
   tetraedro->cambiar_visualizacion(modo);
}
