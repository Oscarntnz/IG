// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

enum EnumEjes : unsigned int {E_X = 0, E_Y = 1, E_Z = 2};

class ObjRevolucion : public Malla3D
{
    public:
        ObjRevolucion();
        ObjRevolucion(const std::string & archivo, int num_instancias, 
        EnumEjes rotacion_eje = EnumEjes::E_Y, bool tapa_sup = true, bool tapa_inf = true);
        ObjRevolucion(std::vector<Tupla3f> perfil_original, int num_instancias, 
        EnumEjes rotacion_eje = EnumEjes::E_Y, bool tapa_sup = true, bool tapa_inf = true);
        
        void toggleTapas(bool inferior, bool superior);

    private:
        // Atributos
        std::vector<Tupla3f> tabla_v;   // tabla de vértices
        std::vector<Tupla3i> tabla_c;   // tabla de caras
        int M, N;                       // número de vértices del perfil y número de rotaciones
        Tupla3f polo_s, polo_i;

        // Funciones

        void ordenarPuntos();
        void eliminarPolos();
        Tupla3f calcularVectorRotado(int j, float factor_rotacion);
        void anadirTapas(bool inferior, bool superior);
        void eliminarTapas(bool inferior, bool superior);
        std::pair<bool,bool> crearPolos();      // calcula los polos, si no los tiene los crea, devuelve bool
                                                // para saber si los tenia o no
    protected:
        // Atributos

        std::vector<Tupla3f> perfil;
        std::pair<bool,bool> tapas;     // tapas: inerior, superior
        EnumEjes eje_rotacion;

        // Funciones

        void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool conTapas);
        void crearPerfilDebug();

} ;




#endif
