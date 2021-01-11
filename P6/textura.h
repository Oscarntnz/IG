#ifndef TEXTURA_H_
#define TEXTURA_H_

#include "aux.h"
#include <string>

class Textura {
    private:
    GLuint textura_id = -1;
    std::vector<unsigned char> data;
    unsigned char * texels;
    int width, height;
    static const std::string rutaTex;

    public:
    Textura(std::string archivo);
    ~Textura() = default;
    void activar();

    inline const GLuint getID()const{
        return textura_id;
    }
};

#endif