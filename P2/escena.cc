#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "menuctl.h"

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena(): menu_ctl(), objetos_escena(0)
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;
    objeto_a_dibujar = Objetos::NULO;

    ejes.changeAxisSize(5000);

    // crear los objetos de la escena

    cubo = new Cubo(100);
    tetraedro = new Tetraedro(100);
    objply = new ObjPLY("./plys/beethoven");
    cono = new Cono(100, 50, 50);
    cilindro = new Cilindro(2, 25, 100, 25);

    objetos_escena.push_back(cubo);
    objetos_escena.push_back(tetraedro);
    objetos_escena.push_back(objply);
    objetos_escena.push_back(cilindro);
    objetos_escena.push_back(cono);
    //objetos_escena.push_back(nullptr);
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	//glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
   glClearColor( 0.0, 0.05, 0.10, 1.0 );

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

   glEnable(GL_CULL_FACE);

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

   change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );

   std::cout << std::endl << "Practica IG:" << std::endl << std::endl;
   menu_ctl.menuPrincipal();
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

   for(int i = 0; i < objetos_escena.size(); ++i){
      if(objeto_a_dibujar == Objetos(i) || objetos_escena[i]->get_visibility()){
         if(objeto_a_dibujar == Objetos::PLY)
            ajusta_ply();
         objetos_escena[i]->draw();
         objeto_a_dibujar == Objetos::NULO;
      }
   }

   /*if(objeto_a_dibujar == Objetos::CUBO || cubo->get_visibility()){
      cubo->draw();
      objeto_a_dibujar == Objetos::NULO;
   }
   if(objeto_a_dibujar == Objetos::TETRAEDRO || tetraedro->get_visibility()){
      tetraedro->draw();
      objeto_a_dibujar == Objetos::NULO;
   }
   if(objeto_a_dibujar == Objetos::PLY || objply->get_visibility()){
      ajusta_ply();
      objply->draw();
      objeto_a_dibujar == Objetos::NULO;
   }
   if(objeto_a_dibujar == Objetos::CONO || cono->get_visibility()){
      cono->draw();
      objeto_a_dibujar == Objetos::NULO;
   }*/
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
            menu_ctl.selObjeto();
         }
         else
            menu_ctl.noValido();

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
               objeto_a_dibujar = Objetos::NULO;
            }
            menu_ctl.muestraObjeto("cubo", cubo->get_visibility());
            modoMenu = NADA;
         }
         else
            menu_ctl.noValido();

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
               objeto_a_dibujar = Objetos::NULO;
            }
            menu_ctl.muestraObjeto("tetraedro", tetraedro->get_visibility());
            modoMenu = NADA;
         }
         else
            menu_ctl.noValido();

         break ;

         case 'Y' :
         // ESTAMOS SELECCIONANDO EL CONO
         if(modoMenu == SELOBJETO){
            if(!cono->get_visibility()){
               objeto_a_dibujar = Objetos::CONO;
               cono->toggle_visibility();
            }
            else{
               cono->toggle_visibility();
               objeto_a_dibujar = Objetos::NULO;
            }
            menu_ctl.muestraObjeto("cono", cono->get_visibility());
            modoMenu = NADA;
         }
         else
            menu_ctl.noValido();

         break ;

         case 'H' :
         // ESTAMOS SELECCIONANDO EL CILINDRO
         if(modoMenu == SELOBJETO){
            if(!cilindro->get_visibility()){
               objeto_a_dibujar = Objetos::CILINDRO;
               cilindro->toggle_visibility();
            }
            else{
               cilindro->toggle_visibility();
               objeto_a_dibujar = Objetos::NULO;
            }
            menu_ctl.muestraObjeto("cilindro", cilindro->get_visibility());
            modoMenu = NADA;
         }
         else
            menu_ctl.noValido();

         break ;

      case 'V' :
         // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
         if (modoMenu==NADA && modoMenu!=SELVISUALIZACION){
            modoMenu=SELVISUALIZACION;
            menu_ctl.selVisualizacion();
         }
         else
            menu_ctl.noValido();

         break ;
      
      // OPCIONES DE SELECCION DE VISUALIZACION

      case 'P' :
         // ESTAMOS SELECCIONANDO MODO DE VISUALIZACION PUNTOS
         if (modoMenu==SELVISUALIZACION){
            cambiar_visualizacion(ModoVisualizacion::PUNTOS);
            menu_ctl.cambiado("puntos");
            modoMenu=NADA;
         }
         // ESTAMOS SELECCIONANDO EL OBJETO PLY
         else if(modoMenu==SELOBJETO){
            if(!tetraedro->get_visibility()){
               objeto_a_dibujar = Objetos::PLY;
               objply->toggle_visibility();
            }
            else{
               objply->toggle_visibility();
               objeto_a_dibujar = Objetos::NULO;
            }
            menu_ctl.muestraObjeto("objeto ply", objply->get_visibility());
            modoMenu = NADA;
         }
         else
            menu_ctl.noValido();
         
         break;

      case 'L' :
         // ESTAMOS SELECCIONANDO MODO DE VISUALIZACION LINEAS
         if (modoMenu==SELVISUALIZACION){
            cambiar_visualizacion(ModoVisualizacion::LINEAS);
            menu_ctl.cambiado("lineas");
            modoMenu=NADA;
         }
         else
            menu_ctl.noValido();
         
         break;

      case 'S' :
         // ESTAMOS SELECCIONANDO MODO DE VISUALIZACION SOLIDO
         if (modoMenu==SELVISUALIZACION){
            cambiar_visualizacion(ModoVisualizacion::SOLIDO);
            menu_ctl.cambiado("solido");
            modoMenu=NADA;
         }
         else
            menu_ctl.noValido();
         
         break;

      case 'A' :
         // ESTAMOS SELECCIONANDO MODO DE VISUALIZACION AJEDREZ
         if (modoMenu==SELVISUALIZACION){
            cambiar_visualizacion(ModoVisualizacion::AJEDREZ);
            menu_ctl.cambiado("ajedrez");
            modoMenu=NADA;
         }
         else
            menu_ctl.noValido();
         
         break;

      case 'D' :
         // ESTAMOS EN MODO SELECCION DE DIBUJADO
         if (modoMenu==NADA && modoMenu!=SELDIBUJADO){
            modoMenu=SELDIBUJADO;
            menu_ctl.selDibujado();
         }
         else
            menu_ctl.noValido();

         break;
      
      // OPCIONES DE SELECCION DE DIBUJADO
      
      case '1' :
         // ESTAMOS SELECCIONANDO MODO DE DIBUJADO INMEDIATO
         if (modoMenu==SELDIBUJADO){
            cambiar_dibujado(ModoDibujado::INMEDIATO);
            menu_ctl.modoDibujado("inmediato");
            modoMenu=NADA;
         }
         else
            menu_ctl.noValido();
         
         break;
      case '2' :
         // ESTAMOS SELECCIONANDO MODO DE DIBUJADO DIFERIDO
         if (modoMenu==SELDIBUJADO){
            cambiar_dibujado(ModoDibujado::DIFERIDO);
            menu_ctl.modoDibujado("diferido");
            modoMenu=NADA;
         }
         else
            menu_ctl.noValido();
         
         break;
      default:
         menu_ctl.noValido();
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
   for(auto it = objetos_escena.begin(); it != objetos_escena.end(); ++it)
      (*it)->cambiar_dibujado(modo);
}

void Escena::cambiar_visualizacion(ModoVisualizacion modo){
   for(auto it = objetos_escena.begin(); it != objetos_escena.end(); ++it)
      (*it)->cambiar_visualizacion(modo);
}

void Escena::ajusta_ply(){
   if(objply->getNombre().compare("krillin") == 0){
      glRotatef(-90, 1, 0, 0);
      glRotatef(180, 0, 0, 1);
   }
   glScalef(30.0,30.0,30.0);
}