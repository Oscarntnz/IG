// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: cilindro.h

//
// #############################################################################

#ifndef OBJPLY_H_INCLUDED
#define OBJPLY_H_INCLUDED

#include "aux.h"
#include "ply_reader.h"
#include "malla.h"
#include <string>

 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************
class ObjPLY: public Malla3D {
    private:
        std::string nombre;

    public:
        ObjPLY(const std::string & nombre_archivo);
        const std::string & getNombre();
        
};

#endif


