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
#include "camara.h"
#include "bath.h"
#include "jarron.h"
#include "lata.h"

typedef enum
{
    NADA,
    SELOBJETO,
    SELVISUALIZACION,
    SELDIBUJADO,
    SELILUMINACION,
    SELCAMARA,
    VARALPHA,
    VARBETA,
    SELGLIB
} menu;

enum EstadoRaton
{
    MOVIENDO_CAMARA_FIRSTPERSON,
    MOVIENDO_CAMARA_EXAMINAR,
    NEUTRAL
};

class Escena
{
private:
    // Atributos

    GLfloat Observer_distance;                          // variables que definen la posicion de la camara en coordenadas polares
    GLfloat Observer_angle_x;
    GLfloat Observer_angle_y;
    GLfloat Width, Height, Front_plane, Back_plane;     // variables que controlan la ventana y la transformacion de perspectiva
    MenuCtl menu_ctl;
    unsigned int gLib = UINT_MAX;
    bool animar = true;
    std::vector<float> velocAnimacion;
    std::pair<int, int> raton;
    EstadoRaton estadoRaton;
    size_t camaraActiva;
    int objSeleccionado;
    size_t camara_cabeza;
    menu modoMenu = NADA;
    std::vector<Malla3D *> objetos_escena;
    Ejes ejes;
    Cubo *cubo = nullptr;           // es importante inicializarlo a 'nullptr'
    Tetraedro *tetraedro = nullptr; // es importante inicializarlo a 'nullptr'
    ObjPLY *bathtub = nullptr;
    Cono *cono = nullptr;
    Cilindro *cilindro = nullptr;
    Esfera *esfera = nullptr;
    ObjRevolucion *objrevo = nullptr;
    ObjRevolucion *objrevo2 = nullptr;
    Cuadro *cuadro = nullptr;
    ObjRevolucion *lata = nullptr;
    Krillin *krillin = nullptr;
    Bath *bath = nullptr;
    ObjPLY *sink = nullptr;
    ObjPLY *toilet = nullptr;
    Jarron *jarron = nullptr;
    std::vector<Tupla3f> pos_objetos;
    Tupla3f pos_krillin, pos_cabeza;
    std::vector<Tupla3f> escalas_objetos;
    std::vector<Tupla3f> rotacion_objetos;
    std::vector<Luz *> luces;
    std::vector<Camara *> camaras;
    std::vector<Tupla3f> coloresModoSeleccion;

    //Funciones

    void cambiar_dibujado(ModoDibujado modo);
    void cambiar_visualizacion(ModoVisualizacion modo);
    void cambiaTapas();
    void ajustar_objeto(int i);
    GLenum toggle_sombreado();
    void dibuja_objetos();
    void dibujaSeleccion();
    void dibuja_luces();
    void modifGLib(int grado, bool aumentar);
    void modifVeloc(float factor);
    int getObjeto(Tupla3f color);
    bool igualQue(Tupla3f color1, Tupla3f color2);
    void seleccion();
    void cambia_camara(int camara);
    void change_projection(const float ratio_xy);   // Transformación de cámara
    void change_observer();
    void clear_window();

public:
    Escena();
    void inicializar(int UI_window_width, int UI_window_height);
    void redimensionar(int newWidth, int newHeight);

    // Dibujar
    void dibujar();

    // Interacción con la escena
    bool teclaPulsada(unsigned char Tecla1, int x, int y);
    void teclaEspecial(int Tecla1, int x, int y);
    void clickRaton(int boton, int estado, int x, int y);
    void ratonMovido(int x, int y);

    // Animacion
    void animarModeloJerarquico();
};
#endif
