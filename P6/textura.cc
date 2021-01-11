#include "textura.h"
#include "jpg_imagen.hpp"

const std::string Textura::rutaTex = "./texturas/";

Textura::Textura(std::string archivo): data(0){
    jpg::Imagen * pimg = nullptr;

    pimg = new jpg::Imagen(rutaTex + archivo + ".jpg");

    width = pimg->tamX(); // núm. columnas (unsigned)
    height = pimg->tamY(); // núm. filas (unsigned)
    texels = pimg->leerPixels(); // puntero texels (unsigned char *)

    for(int i = 0; i < width*height*3; ++i)
        data.push_back(*(texels + i));
}

void Textura::activar(){  
    glEnable(GL_TEXTURE_2D);

    if(textura_id == (GLuint)-1){
        glGenTextures(1 , &textura_id); // idTex almacena el nuevo identificador
        glBindTexture(GL_TEXTURE_2D , getID()); // activa textura con id ’idTex’
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data.data());
    }

    glBindTexture(GL_TEXTURE_2D , getID());
}