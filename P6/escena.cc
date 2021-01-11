#include "aux.h"              // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h"            // objetos: Cubo y otros....
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "menuctl.h"
#include "cono.h"
#include "cilindro.h"
#include "esfera.h"
#include <limits>

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena() : menu_ctl(), velocAnimacion(0), objetos_escena(0), pos_objetos(0), escalas_objetos(0), luces(0), camaras(0)
{
   Front_plane = 50.0;
   Back_plane = 2000.0;
   Observer_distance = 4 * Front_plane;
   Observer_angle_x = 0.0;
   Observer_angle_y = 0.0;
   raton.first = 0;
   raton.second = 0;
   estadoRaton = EstadoRaton::NEUTRAL;
   camaraActiva = 0;
   objSeleccionado = -1;
   camara_cabeza = 2;

   ejes.changeAxisSize(5000);

   // crear los objetos de la escena

   cubo = new Cubo(2.5);
   tetraedro = new Tetraedro(2.5);
   bathtub = new ObjPLY("./plys/bathtub");
   cilindro = new Cilindro(20, 20, 5, 2.5, EnumEjes::E_Y, true);
   cono = new Cono(4, 20, 5, 2.5, EnumEjes::E_Y, true);
   esfera = new Esfera(20, 20, 2, EnumEjes::E_Z, true);
   objrevo = new ObjRevolucion("./plys/peon", 20, EnumEjes::E_Y, true, true, true);
   objrevo2 = new ObjRevolucion("./plys/peon", 20, EnumEjes::E_Y, true, true, true);
   cuadro = new Cuadro(2.5, "betis");
   lata = new ObjRevolucion("./plys/lata-pcue.ply", 20, EnumEjes::E_Y, false, false, false);
   bath = new Bath();
   sink = new ObjPLY("./plys/sink");
   toilet = new ObjPLY("./plys/toilet");
   jarron = new Jarron(20, true);
   krillin = new Krillin();
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar(int UI_window_width, int UI_window_height)
{
   glClearColor(1.0, 1.0, 1.0, 1.0); // se indica cual sera el color para limpiar la ventana	(r,v,a,al)

   glEnable(GL_DEPTH_TEST); // se habilita el z-bufer
   glEnable(GL_CULL_FACE);
   glEnable(GL_NORMALIZE);

   Width = UI_window_width/10;
   Height = UI_window_height/10;

   // Peones

   objrevo->setColor({0.95, 0.95, 0.95}, {0.95, 0.95, 0.95});
   objrevo2->setColor({0.2, 0.2, 0.2}, {0.2, 0.2, 0.2});

   // emerald modificado

   Tupla4f ambiente = {0.0215, 0.1745, 0.0215, 1.0},
           difuso = {0.07568, 0.061424, 0.07568, 1.0},
           especular = {0.0, 0.0, 0.0, 1.0};
   float brillo = 0.01 * 128;
   Material m(ambiente, difuso, especular, brillo);
   jarron->setMaterial(m);

   // black plastic modificado

   ambiente = {0.0, 0.0, 0.0, 1.0},
   difuso = {0.01, 0.01, 0.01, 1.0},
   especular = {0.50, 0.50, 0.50, 1.0};
   brillo = 0.7 * 128;
   Material m2(ambiente, difuso, especular, brillo);
   objrevo2->setMaterial(m2);

   ambiente = {0.0, 0.0, 0.0, 1.0},
   difuso = {0.55, 0.55, 0.55, 1.0},
   especular = {0.7, 0.7, 0.7, 1.0};
   brillo = 0.25 * 128;
   Material porcelana(ambiente, difuso, especular, brillo);
   bath->setMaterial(porcelana);
   toilet->setMaterial(porcelana);
   sink->setMaterial(porcelana);
   bathtub->setMaterial(porcelana);
   cilindro->setMaterial(porcelana);
   bathtub->setMaterial(porcelana);
   objrevo->setMaterial(porcelana);

   ambiente = {0.05, 0.05, 0.0, 1.0},
   difuso = {0.5, 0.5, 0.4, 1.0},
   especular = {0.7, 0.7, 0.04, 1.0};
   brillo = 0.25 * 128;
   Material cristal(ambiente, difuso, especular, brillo);
   cubo->setMaterial(cristal);
   cuadro->setMaterial(cristal);
   lata->setMaterial(cristal);
   esfera->setMaterial(cristal);
   cono->setMaterial(cristal);

   ambiente = {0.2, 0.2, 0.2, 1.0};
   difuso = {0.8, 0.8, 0.8, 1.0};
   especular = {0.0, 0.0, 0.0, 1.0};
   brillo = 0.2*128;
   Material m3(ambiente, difuso, especular, brillo);
   tetraedro->setMaterial(m3);

   tetraedro->setTextura("text-madera");
   esfera->setTextura("tierra");
   lata->setTextura("text-lata-1");
   cono->setTextura("tierra");

   cubo->setColor({0.9, 1.0, 1.0}, {0.9, 1.0, 1.0});
   bathtub->setColor({0.9, 0.9, 0.9}, {0.9, 0.9, 0.9});
   sink->setColor({0.9, 0.9, 0.9}, {0.9, 0.9, 0.9});
   toilet->setColor({0.9, 0.9, 0.9}, {0.9, 0.9, 0.9});
   cilindro->setColor({0.5, 0.5, 0.5}, {0.5, 0.5, 0.5});

   objetos_escena.push_back(cubo);
   objetos_escena.push_back(tetraedro);
   objetos_escena.push_back(bathtub);
   objetos_escena.push_back(cilindro);
   objetos_escena.push_back(cono);
   objetos_escena.push_back(esfera);
   objetos_escena.push_back(objrevo);
   objetos_escena.push_back(objrevo2);
   objetos_escena.push_back(cuadro);
   objetos_escena.push_back(lata);
   objetos_escena.push_back(bath);
   objetos_escena.push_back(sink);
   objetos_escena.push_back(toilet);
   objetos_escena.push_back(jarron);

   pos_objetos.push_back({0.0, 350.0, 0.0});
   pos_objetos.push_back({-500.0, -50.0, -250.0});
   pos_objetos.push_back({500.0, -10.0, 0.0});
   pos_objetos.push_back({-50.0, -50.0, -300.0});
   pos_objetos.push_back({-200.0, -50.0, -300.0});
   pos_objetos.push_back({450.0, 50.0, -300.0});
   pos_objetos.push_back({300.0, -40.0, -300.0});
   pos_objetos.push_back({100.0, -40.0, -300.0});
   pos_objetos.push_back({100.0, 250.0, -370.0});
   pos_objetos.push_back({-300.0, 115.0, -260.0});
   pos_objetos.push_back({0.0, 125.0, 0.0});
   pos_objetos.push_back({-325.0, 25.0, -225.0});
   pos_objetos.push_back({200.0, 40.0, -300.0});
   pos_objetos.push_back({450.0, -70.0, -300.0});
   pos_krillin = {325.0, 10.0, 225.0};
   pos_objetos.push_back(pos_krillin);

   rotacion_objetos.push_back({0.0, 0.0, 0.0});
   rotacion_objetos.push_back({0.0, 0.0, 0.0});
   rotacion_objetos.push_back({0.0, -90.0, 0.0});
   rotacion_objetos.push_back({0.0, 0.0, 0.0});
   rotacion_objetos.push_back({0.0, 0.0, 0.0});
   rotacion_objetos.push_back({0.0, 0.0, 0.0});
   rotacion_objetos.push_back({0.0, 0.0, 0.0});
   rotacion_objetos.push_back({0.0, 0.0, 0.0});
   rotacion_objetos.push_back({0.0, 0.0, 0.0});
   rotacion_objetos.push_back({0.0, 180.0, 0.0});
   rotacion_objetos.push_back({0.0, 0.0, 0.0});
   rotacion_objetos.push_back({0.0, 0.0, 0.0});
   rotacion_objetos.push_back({0.0, 0.0, 0.0});
   rotacion_objetos.push_back({0.0, 0.0, 0.0});
   rotacion_objetos.push_back({0.0, -90.0, 0.0});

   escalas_objetos.push_back({200.0, 10.0, 10.0});
   escalas_objetos.push_back({75.0, 100.0, 75.0});
   escalas_objetos.push_back({20.0, 20.0, 20.0});
   escalas_objetos.push_back({25.0, 25.0, 25.0});
   escalas_objetos.push_back({25.0, 25.0, 25.0});
   escalas_objetos.push_back({30.0, 30.0, 30.0});
   escalas_objetos.push_back({60.0, 60.0, 60.0});
   escalas_objetos.push_back({60.0, 60.0, 60.0});
   escalas_objetos.push_back({100.0, 75.0, 0.0});
   escalas_objetos.push_back({50.0, 50.0, 50.0});
   escalas_objetos.push_back({1250.0, 500.0, 750.0});
   escalas_objetos.push_back({2.0, 2.25, 2.0});
   escalas_objetos.push_back({4.0, 4.0, 4.0});
   escalas_objetos.push_back({40.0, 60.0, 40.0});
   escalas_objetos.push_back({25.0, 25.0, 25.0});

   coloresModoSeleccion.push_back({1.0, 0.0, 0.0});
   coloresModoSeleccion.push_back({1.0, 0.5, 0.0});
   coloresModoSeleccion.push_back({1.0, 0.0, 1.0});
   coloresModoSeleccion.push_back({1.0, 1.0, 0.5});
   coloresModoSeleccion.push_back({0.0, 1.0, 0.0});
   coloresModoSeleccion.push_back({0.0, 1.0, 1.0});
   coloresModoSeleccion.push_back({0.0, 0.0, 1.0});
   coloresModoSeleccion.push_back({0.5, 0.0, 0.0});
   coloresModoSeleccion.push_back({0.5, 0.5, 0.0});
   coloresModoSeleccion.push_back({0.5, 0.0, 0.5});
   coloresModoSeleccion.push_back({0.5, 0.5, 0.5});
   coloresModoSeleccion.push_back({0.5, 0.5, 1.0});
   coloresModoSeleccion.push_back({0.5, 1.0, 1.0});
   coloresModoSeleccion.push_back({0.5, 1.0, 0.5});
   coloresModoSeleccion.push_back({1.0, 0.5, 1.0});

   krillin->rotarAntebrazoD(-45.0, EnumEjes::E_X);
   krillin->rotarBrazoI(-90.0, EnumEjes::E_Z);

   luces.push_back(new LuzPosicional({0.0, 275.0, 0.0}, GL_LIGHT0,
                                     {0.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}));
   luces.push_back(new LuzDireccional({M_PI/2.0, M_PI}, GL_LIGHT1,
                                      {0.0, 0.0, 0.0, 1.0}, {0.0, 0.0, 0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}));

   velocAnimacion.push_back(1.0);
   velocAnimacion.push_back(1.0);
   velocAnimacion.push_back(1.0);

   luces[0]->toggleEnabled();
   luces[1]->toggleEnabled();

   pos_cabeza = pos_krillin + Tupla3f(0.0, 80.0, 5.0);

   camaras.push_back(new Camara({0.0, 10.0, 210.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, TipoCamara::PERSPECTIVA, -Width, Width, Front_plane, Back_plane));
   camaras.push_back(new Camara({-400.0, 200.0, 200.0}, pos_krillin, {0.0, 1.0, 0.0}, TipoCamara::ORTOGONAL, -Width*2, Width*2, Front_plane, Back_plane));
   camaras.push_back(new Camara(pos_cabeza, {0.0, 0.0, 100.0}, {0.0, 1.0, 0.0}, TipoCamara::PERSPECTIVA, -Width, Width, Front_plane, Back_plane));

   for(size_t i = 0; i < objetos_escena.size(); ++i)
      objetos_escena[i]->setColorModoSelec(coloresModoSeleccion[i]);

   krillin->setColorModoSelec(coloresModoSeleccion[objetos_escena.size()]);

   change_projection(float(UI_window_width) / float(UI_window_height));
   glViewport(0, 0, UI_window_width, UI_window_height);

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
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
   change_observer();
   glDisable(GL_LIGHTING);
   ejes.draw();

   // Dibujar las distintas luces de la escena

   dibuja_luces();

   // Dibujar los diferentes elementos de la escena

   dibuja_objetos();
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada(unsigned char tecla, int x, int y)
{
   using namespace std;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;
   bool salir = false;
   switch (toupper(tecla))
   {
   case 'Q':
      if (modoMenu == VARALPHA || modoMenu == VARBETA)
      {
         modoMenu = SELILUMINACION;
         menu_ctl.modoIluminacion();
      }
      else if (modoMenu == SELGLIB)
      {
         gLib = UINT_MAX;
         modoMenu = NADA;
         menu_ctl.menuPrincipal();
      }
      else if (modoMenu != NADA)
      {
         modoMenu = NADA;
         menu_ctl.menuPrincipal();
      }
      else
      {
         salir = true;
      }
      break;
   case 'O':
      // ESTAMOS EN MODO SELECCION DE OBJETO
      if (modoMenu == NADA && modoMenu != SELOBJETO)
      {
         modoMenu = SELOBJETO;
         menu_ctl.selObjeto();
      }
      else
         menu_ctl.noValido();

      break;

      // OPCIONES DE SELECCION DE OBJETO

   case 'C':
      // ESTAMOS SELECCIONANDO EL CUBO
      if (modoMenu == SELOBJETO)
      {
         if (!cubo->get_visibility())
         {
            cubo->toggle_visibility();
         }
         else
         {
            cubo->toggle_visibility();
         }
         menu_ctl.muestraObjeto("cubo", cubo->get_visibility());
         modoMenu = NADA;
      }
      else if (modoMenu == NADA)
      {
         modoMenu = SELCAMARA;
         menu_ctl.selCamara(camaras.size());
      }
      else
         menu_ctl.noValido();

      break;
   case 'T':
      // ESTAMOS SELECCIONANDO EL TETRAEDRO
      if (modoMenu == SELOBJETO)
      {
         if (!tetraedro->get_visibility())
         {
            tetraedro->toggle_visibility();
         }
         else
         {
            tetraedro->toggle_visibility();
         }
         menu_ctl.muestraObjeto("tetraedro", tetraedro->get_visibility());
         modoMenu = NADA;
      }
      // ESTAMOS EN MODO SELECCION DE TAPA
      else if (modoMenu == NADA)
      {
         menu_ctl.selTapa();
         cambiaTapas();
      }
      else
         menu_ctl.noValido();

      break;

   case 'Y':
      // ESTAMOS SELECCIONANDO EL CONO
      if (modoMenu == SELOBJETO)
      {
         if (!cono->get_visibility())
         {
            cono->toggle_visibility();
         }
         else
         {
            cono->toggle_visibility();
         }
         menu_ctl.muestraObjeto("cono", cono->get_visibility());
         modoMenu = NADA;
      }
      else
         menu_ctl.noValido();

      break;

   case 'H':
      // ESTAMOS SELECCIONANDO EL CILINDRO
      if (modoMenu == SELOBJETO)
      {
         if (!cilindro->get_visibility())
         {
            cilindro->toggle_visibility();
         }
         else
         {
            cilindro->toggle_visibility();
         }
         menu_ctl.muestraObjeto("cilindro", cilindro->get_visibility());
         modoMenu = NADA;
      }
      else
         menu_ctl.noValido();

      break;

   case 'E':
      // ESTAMOS SELECCIONANDO LA ESFERA
      if (modoMenu == SELOBJETO)
      {
         if (!esfera->get_visibility())
         {
            esfera->toggle_visibility();
         }
         else
         {
            esfera->toggle_visibility();
         }
         menu_ctl.muestraObjeto("esfera", esfera->get_visibility());
         modoMenu = NADA;
      }
      else
         menu_ctl.noValido();

      break;

   case 'R':
      // ESTAMOS SELECCIONANDO EL OBJETO REVOLUCION
      if (modoMenu == SELOBJETO)
      {
         if (!objrevo->get_visibility())
         {
            objrevo->toggle_visibility();
         }
         else
         {
            objrevo->toggle_visibility();
         }
         menu_ctl.muestraObjeto("objeto revolucion", objrevo->get_visibility());
         modoMenu = NADA;
      }
      else
         menu_ctl.noValido();

      break;

   case 'V':
      // ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
      if (modoMenu == NADA && modoMenu != SELVISUALIZACION)
      {
         modoMenu = SELVISUALIZACION;
         menu_ctl.selVisualizacion();
      }
      else
         menu_ctl.noValido();

      break;

      // OPCIONES DE SELECCION DE VISUALIZACION

   case 'P':
      // ESTAMOS SELECCIONANDO MODO DE VISUALIZACION PUNTOS
      if (modoMenu == SELVISUALIZACION)
      {
         cambiar_visualizacion(ModoVisualizacion::PUNTOS);
         menu_ctl.cambiado("puntos");
         modoMenu = NADA;
      }
      // ESTAMOS SELECCIONANDO EL OBJETO PLY
      else if (modoMenu == SELOBJETO)
      {
         if (!tetraedro->get_visibility())
         {
            bathtub->toggle_visibility();
         }
         else
         {
            bathtub->toggle_visibility();
         }
         menu_ctl.muestraObjeto("objeto ply", bathtub->get_visibility());
         modoMenu = NADA;
      }
      else
         menu_ctl.noValido();

      break;

   case 'L':
      // ESTAMOS SELECCIONANDO MODO DE VISUALIZACION LINEAS
      if (modoMenu == SELVISUALIZACION)
      {
         cambiar_visualizacion(ModoVisualizacion::LINEAS);
         menu_ctl.cambiado("lineas");
         modoMenu = NADA;
      }
      else
         menu_ctl.noValido();

      break;

   case 'S':
      // ESTAMOS SELECCIONANDO MODO DE VISUALIZACION SOLIDO
      if (modoMenu == SELVISUALIZACION)
      {
         cambiar_visualizacion(ModoVisualizacion::SOLIDO);
         menu_ctl.cambiado("solido");
         modoMenu = NADA;
      }
      // ESTAMOS CAMBIANDO LA FORMA DE SOMBREADO
      else if (modoMenu == SELILUMINACION)
      {
         menu_ctl.cambiadoSombreado(toggle_sombreado());
      }
      else
         menu_ctl.noValido();

      break;

   case 'A':
      // ESTAMOS SELECCIONANDO MODO DE VISUALIZACION AJEDREZ
      if (modoMenu == SELVISUALIZACION)
      {
         cambiar_visualizacion(ModoVisualizacion::AJEDREZ);
         menu_ctl.cambiado("ajedrez");
         modoMenu = NADA;
      }
      else if (modoMenu == SELILUMINACION || modoMenu == VARBETA)
      {
         modoMenu = VARALPHA;
         menu_ctl.cambiarAngulo("alpha");
      }
      else if (modoMenu == NADA && modoMenu != SELGLIB)
      {
         modoMenu = SELGLIB;
         menu_ctl.selGLib(2);
         animar = true;
      }
      else
         menu_ctl.noValido();

      break;

   case 'B':
      if (modoMenu == SELILUMINACION || modoMenu == VARALPHA)
      {
         modoMenu = VARBETA;
         menu_ctl.cambiarAngulo("beta");
      }
      else
         menu_ctl.noValido();

      break;

   case 'I':
      // ESTAMOS SELECCIONANDO ILUMINACION
      if (modoMenu == NADA)
      {
         cambiar_visualizacion(ModoVisualizacion::ILUMINACION);
         menu_ctl.cambiado("iluminacion");
         menu_ctl.modoIluminacion();
         modoMenu = SELILUMINACION;
      }
      else
         menu_ctl.noValido();

      break;

   case 'D':
      // ESTAMOS EN MODO SELECCION DE DIBUJADO
      if (modoMenu == NADA && modoMenu != SELDIBUJADO)
      {
         modoMenu = SELDIBUJADO;
         menu_ctl.selDibujado();
      }
      else
         menu_ctl.noValido();

      break;

   case 'M':
      if (modoMenu == NADA && modoMenu != SELGLIB)
      {
         modoMenu = SELGLIB;
         menu_ctl.selGLib(5);
         animar = false;
      }
      else
         menu_ctl.noValido();

      break;

   case '0':
      // ESTAMOS SELECCIONANDO LA LUZ POSICIONAL
      if (modoMenu == SELILUMINACION)
      {
         luces[0]->toggleEnabled();
         menu_ctl.activadaLuz(luces[0]->getActivada(), 0);
      }
      else if (modoMenu == SELGLIB)
      {
         gLib = 0;
         menu_ctl.seleccionadoGrado(0);
      }
      else if (modoMenu == SELCAMARA)
      {
         cambia_camara(0);
         menu_ctl.seleccionadaCamara(camaraActiva);
         modoMenu = NADA;
      }
      else
         menu_ctl.noValido();
      break;

   case '1':
      // ESTAMOS SELECCIONANDO MODO DE DIBUJADO INMEDIATO
      if (modoMenu == SELDIBUJADO)
      {
         cambiar_dibujado(ModoDibujado::INMEDIATO);
         menu_ctl.modoDibujado("inmediato");
         modoMenu = NADA;
      }
      // ESTAMOS SELECCIONANDO LA LUZ DIRECCIONAL
      else if (modoMenu == SELILUMINACION)
      {
         luces[1]->toggleEnabled();
         menu_ctl.activadaLuz(luces[1]->getActivada(), 1);
      }
      else if (modoMenu == SELGLIB)
      {
         gLib = 1;
         menu_ctl.seleccionadoGrado(1);
      }
      else if (modoMenu == SELCAMARA)
      {
         cambia_camara(1);
         menu_ctl.seleccionadaCamara(camaraActiva);
         modoMenu = NADA;
      }
      else
         menu_ctl.noValido();

      break;
   case '2':
      // ESTAMOS SELECCIONANDO MODO DE DIBUJADO DIFERIDO
      if (modoMenu == SELDIBUJADO)
      {
         cambiar_dibujado(ModoDibujado::DIFERIDO);
         menu_ctl.modoDibujado("diferido");
         modoMenu = NADA;
      }
      else if (modoMenu == SELGLIB)
      {
         gLib = 2;
         menu_ctl.seleccionadoGrado(2);
      }
      else if (modoMenu == SELCAMARA)
      {
         cambia_camara(2);
         menu_ctl.seleccionadaCamara(camaraActiva);
         modoMenu = NADA;
      }
      else
         menu_ctl.noValido();

      break;

   case '3':
      if (modoMenu == SELGLIB)
      {
         gLib = 3;
         menu_ctl.seleccionadoGrado(3);
      }
      else
         menu_ctl.noValido();
      break;
   case '4':
      if (modoMenu == SELGLIB)
      {
         gLib = 4;
         menu_ctl.seleccionadoGrado(4);
      }
      else
         menu_ctl.noValido();
      break;
   case '5':
      if (modoMenu == SELGLIB)
      {
         gLib = 5;
         menu_ctl.seleccionadoGrado(5);
      }
      else
         menu_ctl.noValido();
      break;

   case '<':
      // ESTAMOS VARIANDO EL ANGULO ALPHA
      if (modoMenu == VARALPHA)
      {
         dynamic_cast<LuzDireccional *>(luces[1])->variarAnguloAlpha(-3.0);
      }
      // ESTAMOS VARIANDO EL ANGULO BETA
      else if (modoMenu == VARBETA)
      {
         dynamic_cast<LuzDireccional *>(luces[1])->variarAnguloBeta(-3.0);
      }
      else
         menu_ctl.noValido();
      break;

   case '>':
      // ESTAMOS VARIANDO EL ANGULO ALPHA
      if (modoMenu == VARALPHA)
      {
         dynamic_cast<LuzDireccional *>(luces[1])->variarAnguloAlpha(3.0);
      }
      // ESTAMOS VARIANDO EL ANGULO BETA
      else if (modoMenu == VARBETA)
      {
         dynamic_cast<LuzDireccional *>(luces[1])->variarAnguloBeta(3.0);
      }
      else
         menu_ctl.noValido();
      break;

   case '+':
      if (modoMenu == SELGLIB)
      {
         if (animar && (velocAnimacion.size() > gLib || gLib == UINT_MAX))
            modifVeloc(0.1);
         else
            modifGLib(gLib, true);
      }
      else
         menu_ctl.noValido();
      break;

   case '-':
      if (modoMenu == SELGLIB)
      {
         if (animar && (velocAnimacion.size() > gLib || gLib == UINT_MAX))
            modifVeloc(-0.1);
         else
            modifGLib(gLib, false);
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

void Escena::teclaEspecial(int Tecla1, int x, int y)
{
   switch (Tecla1)
   {
   case GLUT_KEY_LEFT:
      camaras[camaraActiva]->mover(-3, 0, 0);
      break;
   case GLUT_KEY_RIGHT:
      camaras[camaraActiva]->mover(3, 0, 0);
      break;
   case GLUT_KEY_UP:
      camaras[camaraActiva]->mover(0, 3, 0);
      break;
   case GLUT_KEY_DOWN:
      camaras[camaraActiva]->mover(0, -3, 0);
      break;
   case GLUT_KEY_PAGE_UP:
      camaras[camaraActiva]->mover(0, 0, 3);
      break;
   case GLUT_KEY_PAGE_DOWN:
      camaras[camaraActiva]->mover(0, 0, -3);
      break;
   }

   change_projection(float(Height) / float(Width));
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection(const float ratio_xy)
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   camaras[camaraActiva]->setProyeccion(ratio_xy);
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar(int newWidth, int newHeight)
{
   Width = newWidth / 10;
   Height = newHeight / 10;
   change_projection(float(newHeight) / float(newWidth));
   glViewport(0, 0, newWidth, newHeight);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   camaras[camaraActiva]->setObserver();
}

void Escena::cambiar_dibujado(ModoDibujado modo)
{
   for (auto it = objetos_escena.begin(); it != objetos_escena.end(); ++it)
      (*it)->cambiar_dibujado(modo);

   krillin->cambiar_dibujado(modo);
}

void Escena::cambiar_visualizacion(ModoVisualizacion modo)
{
   for (auto it = objetos_escena.begin(); it != objetos_escena.end(); ++it)
      (*it)->cambiar_visualizacion(modo);

   krillin->cambiar_visualizacion(modo);
}

void Escena::cambiaTapas()
{
   // si es obj revolucion cambia las tapas

   for (auto it = objetos_escena.begin(); it != objetos_escena.end(); ++it)
      if ((*it)->getTipoMalla() == TipoMalla::OBJREVO)
         dynamic_cast<ObjRevolucion *>(*it)->toggleTapas();

   krillin->toggleTapas();
}

void Escena::ajustar_objeto(int i)
{
   glTranslatef(pos_objetos[i](EnumEjes::E_X), pos_objetos[i](EnumEjes::E_Y), pos_objetos[i](EnumEjes::E_Z));
   glRotatef(rotacion_objetos[i](EnumEjes::E_X), 1, 0, 0);
   glRotatef(rotacion_objetos[i](EnumEjes::E_Y), 0, 1, 0);
   glRotatef(rotacion_objetos[i](EnumEjes::E_Z), 0, 0, 1);
   glScalef(escalas_objetos[i](EnumEjes::E_X), escalas_objetos[i](EnumEjes::E_Y), escalas_objetos[i](EnumEjes::E_Z));
}

GLenum Escena::toggle_sombreado()
{
   GLenum sombreado;

   for (auto it = objetos_escena.begin(); it != objetos_escena.end(); ++it)
      sombreado = (*it)->toggleShadeMode();

   krillin->toggleShadeMode();

   return sombreado;
}

void Escena::dibuja_objetos()
{
   for (size_t i = 0; i < objetos_escena.size(); ++i)
   {
      if (objetos_escena[i]->get_visibility())
      {
         glPushMatrix();
            ajustar_objeto(i);
            objetos_escena[i]->draw();
         glPopMatrix();
      }
   }

   glPushMatrix();
      ajustar_objeto(objetos_escena.size());
      krillin->draw();
   glPopMatrix();
}

void Escena::dibuja_luces()
{
   for (size_t i = 0; i < luces.size(); ++i)
      luces[i]->activar();
}

void Escena::modifGLib(int grado, bool aumentar)
{
   switch (grado)
   {
   case 0:
      krillin->rotarBrazoD((aumentar ? 3 : -3), EnumEjes::E_Z);
      break;
   case 1:
      krillin->rotarBrazoI((aumentar ? 3 : -3), EnumEjes::E_Z);
      break;
   case 2:
      krillin->rotarPiernaD((aumentar ? 3 : -3), EnumEjes::E_X);
      break;
   case 3:
      krillin->rotarPiernaI((aumentar ? 3 : -3), EnumEjes::E_X);
      break;
   case 4:
      krillin->rotarCabeza((aumentar ? 3 : -3), EnumEjes::E_Y);
      break;
   case 5:
      krillin->subirBajarCabeza((aumentar ? 0.03 : -0.03));
      break;
   default:
      menu_ctl.errorGrado();
      break;
   }
}

void Escena::animarModeloJerarquico()
{
   static bool aumentar[3] = {false, true, true};

   if (animar)
   {
      if (aumentar[0] && (krillin->getGradosAntebrazoD()(EnumEjes::E_Z) >= 0.0))
         aumentar[0] = false;
      else if (!aumentar[0] && (krillin->getGradosAntebrazoD()(EnumEjes::E_Z) == krillin->getMinGradosAntebrazoD()(EnumEjes::E_Z)))
         aumentar[0] = true;

      if (aumentar[1] && (krillin->getRotacionBrazoI()(EnumEjes::E_Z) >= -45.0))
         aumentar[1] = false;
      else if (!aumentar[1] && (krillin->getRotacionBrazoI()(EnumEjes::E_Z) <= krillin->getMinRotacionBrazoI()(EnumEjes::E_Z)))
         aumentar[1] = true;

      if (aumentar[2] && (krillin->getAlturaCabeza() >= krillin->getMaxAlturaCabeza()))
         aumentar[2] = false;
      else if (!aumentar[2] && (krillin->getAlturaCabeza() <= krillin->getMinAlturaCabeza()))
         aumentar[2] = true;

      krillin->rotarAntebrazoD((aumentar[0] ? 1 * velocAnimacion[0] : -1 * velocAnimacion[0]), EnumEjes::E_Z);
      krillin->rotarBrazoI((aumentar[1] ? 1 * velocAnimacion[1] : -1 * velocAnimacion[1]), EnumEjes::E_Z);
      krillin->subirBajarCabeza((aumentar[2] ? 0.02 * velocAnimacion[2] : -0.02 * velocAnimacion[2]));
      pos_cabeza = pos_cabeza + Tupla3f(0.0, (aumentar[2] ? 1.0 * velocAnimacion[2] : -1.0 * velocAnimacion[2]), 0.0);
      camaras[camara_cabeza]->setEye(pos_cabeza);

      static Tupla4f color = luces[0]->getColor(2);
      static float factor = 1.0;

      if (color(EnumEjes::E_X) <= 0.0 && color(EnumEjes::E_Y) <= 0.0 && color(EnumEjes::E_Z) <= 0.0)
         factor = 1.0;
      else if (color(EnumEjes::E_X) >= 1.0 && color(EnumEjes::E_Y) >= 1.0 && color(EnumEjes::E_Z) >= 1.0)
         factor = -1.0;

      color = color + factor * Tupla4f(0.01, 0.01, 0.01, 0.0);

      luces[0]->setColor(luces[0]->getColor(0), luces[0]->getColor(1), {abs(color(EnumEjes::E_X)), abs(color(EnumEjes::E_Y)), abs(color(EnumEjes::E_Z)), 1.0});
   }
}

void Escena::modifVeloc(float factor)
{
   if (gLib == UINT_MAX)
      for (auto it = velocAnimacion.begin(); it != velocAnimacion.end(); ++it)
         *it += factor;
   else
      velocAnimacion[gLib] += factor;
}

void Escena::clickRaton(int boton, int estado, int x, int y)
{
   raton.first = x;
   raton.second = y;

   if (boton == GLUT_RIGHT_BUTTON)
   {
      if (estado == GLUT_DOWN)
      {
         if (camaras[camaraActiva]->getObjSelec() != -1)
            estadoRaton = EstadoRaton::MOVIENDO_CAMARA_EXAMINAR;
         else
            estadoRaton = EstadoRaton::MOVIENDO_CAMARA_FIRSTPERSON;
      }
      else
         estadoRaton = EstadoRaton::NEUTRAL;
   }
   else if (boton == GLUT_LEFT_BUTTON)
   {
      if (estado == GLUT_DOWN)
      {
         seleccion();
      }
   }
   else if (boton == 3)
   {
      // Mouse wheel up
      camaras[camaraActiva]->zoom(0.9);
      change_projection(float(Height) / float(Width));
   }
   else if (boton == 4)
   {
      // Mouse wheel down
      camaras[camaraActiva]->zoom(1.1);
      change_projection(float(Height) / float(Width));
   }
}

void Escena::ratonMovido(int x, int y)
{
   if (estadoRaton == MOVIENDO_CAMARA_FIRSTPERSON || estadoRaton == MOVIENDO_CAMARA_EXAMINAR)
   {
      camaras[camaraActiva]->girar(x - raton.first, y - raton.second);
      raton.first = x;
      raton.second = y;
   }
}

void Escena::dibujaSeleccion()
{
   glDisable(GL_DITHER);            // deshabilita el degradado
   glDisable(GL_LIGHTING);          // deshabilita la iluminacion
   glDisable(GL_TEXTURE);           // deshabilita las texturas
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   for (size_t i = 0; i < objetos_escena.size(); ++i)
   {
      if (objetos_escena[i]->get_visibility())
      {
         glPushMatrix();
            ajustar_objeto(i);
            objetos_escena[i]->draw(true);
         glPopMatrix();
      }
   }

   glPushMatrix();
      ajustar_objeto(objetos_escena.size());
      krillin->draw(true);
   glPopMatrix();

   glEnable(GL_LIGHTING);
   glEnable(GL_TEXTURE);
   glEnable(GL_DITHER);
}

int Escena::getObjeto(Tupla3f color)
{
   for (int i = 0; i < (int)objetos_escena.size(); ++i)
   {
      if (igualQue(objetos_escena[i]->getColorModoSelec(), color))
         return i;
   }

   if (igualQue(krillin->getColorModoSelec(), color))
      return objetos_escena.size();

   return -1;
}

bool Escena::igualQue(Tupla3f color1, Tupla3f color2)
{
   static const float EPSILON_2_DECIMALES = 0.01;

   if (fabs(color1(0) - color2(0)) < EPSILON_2_DECIMALES &&
       fabs(color1(1) - color2(1)) < EPSILON_2_DECIMALES &&
       fabs(color1(2) - color2(2)) < EPSILON_2_DECIMALES)
      return true;

   return false;
}

void Escena::seleccion()
{
   Tupla3f colorSeleccionado;
   Tupla4i viewport;

   dibujaSeleccion();

   glGetIntegerv(GL_VIEWPORT, viewport);

   glReadPixels(raton.first, viewport(3) - raton.second, 1, 1, GL_RGB, GL_FLOAT, &colorSeleccionado);

   objSeleccionado = getObjeto(colorSeleccionado);

   if (camaras[camaraActiva]->getObjSelec() != objSeleccionado)
      camaras[camaraActiva]->setObjSelec(objSeleccionado);
   else
      camaras[camaraActiva]->setObjSelec(-1);

   if (objSeleccionado != -1)
   {
      if (objSeleccionado < (int)objetos_escena.size())
      {
         if (!objetos_escena[objSeleccionado]->getSeleccionado())
            camaras[camaraActiva]->setAt({pos_objetos[objSeleccionado]});
      }
      else
      {
         if (!krillin->getSeleccionado())
            camaras[camaraActiva]->setAt(pos_objetos[objSeleccionado]);
      }

      menu_ctl.seleccionadoObjeto(objSeleccionado);
   }

   for (int i = 0; i < (int)objetos_escena.size(); ++i)
   {
      if (i == objSeleccionado)
         objetos_escena[i]->setSeleccionado(!objetos_escena[i]->getSeleccionado());
      else if (objSeleccionado != -1)
         objetos_escena[i]->setSeleccionado(false);
   }

   if (objSeleccionado == (int)objetos_escena.size())
      krillin->setSeleccionado(!krillin->getSeleccionado());
   else if (objSeleccionado != -1)
      krillin->setSeleccionado(false);
}

void Escena::cambia_camara(int camara){
   if (objSeleccionado != -1)
   {
      if (objSeleccionado < (int)objetos_escena.size())
         objetos_escena[objSeleccionado]->setSeleccionado(false);
      else
         krillin->setSeleccionado(false);
   }

   camaraActiva = camara;
   objSeleccionado = camaras[camaraActiva]->getObjSelec();

   if (objSeleccionado != -1)
   {
      if (objSeleccionado < (int)objetos_escena.size())
         objetos_escena[objSeleccionado]->setSeleccionado(true);
      else
         krillin->setSeleccionado(true);
   }

   change_projection(float(Height) / float(Width));
}