#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   nombre = nombre_archivo.substr(nombre_archivo.find("plys/")+5,nombre_archivo.size()-(nombre_archivo.find("plys/")+5));
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, this->v, this->f );

   //Inicializacion de los vectores de colores

   reserva_espacio();
   rellenar_v_colores();
}

const std::string & ObjPLY::getNombre(){
   return nombre;
}