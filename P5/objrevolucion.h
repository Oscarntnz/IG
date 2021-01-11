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

class ObjRevolucion : public Malla3D
{
    public:
        ObjRevolucion();
        ObjRevolucion(const std::string & archivo, int num_instancias, 
        EnumEjes rotacion_eje = EnumEjes::E_Y, bool tapa_sup = true, bool tapa_inf = true,
        bool con_tapas = true);
        ObjRevolucion(std::vector<Tupla3f> perfil_original, int num_instancias, 
        EnumEjes rotacion_eje = EnumEjes::E_Y, bool tapa_sup = true, bool tapa_inf = true,
        bool con_tapas = true);
        
        void toggleTapas();

    private:
        // Atributos
        std::vector<Tupla3f> tabla_v;   // tabla de vértices
        std::vector<Tupla3i> tabla_c;   // tabla de caras
        unsigned int M, N;             // número de vértices del perfil y número de rotaciones
        Tupla3f polo_s, polo_i;
        unsigned int tam_con_tapas, tam_sin_tapas, tam_en_uso;

        // Funciones

        void ordenarPuntos();
        void eliminarPolos();
        Tupla3f calcularVectorRotado(int j, float factor_rotacion);
        void anadirTapas();
        void eliminarTapas();
        std::pair<bool,bool> crearPolos();      // calcula los polos, si no los tiene los crea, devuelve bool
                                                // para saber si los tenia o no
        inline virtual const size_t getTamVCaras()const{
            return tam_en_uso;
        }

    protected:
        // Atributos

        std::vector<Tupla3f> perfil;
        bool tapas;
        std::pair<bool, bool> tiene_tapas;      // para saber si le podemos añadir tapa superior o inferior
        EnumEjes eje_rotacion;

        // Funciones

        void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool conTapas);
        void crearPerfilDebug();
        virtual void calcularPuntosTex();

} ;




#endif
