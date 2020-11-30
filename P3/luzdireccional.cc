#include "luzdireccional.h"
#include <cmath>

LuzDireccional::LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f colorAmbiente, Tupla4f colorEspecular,
Tupla4f colorDifuso){
    this->id = idLuzOpenGL;
    this->colorAmbiente = colorAmbiente;
    this->colorEspecular = colorEspecular;
    this->colorAmbiente = colorAmbiente;
    this->alpha = gradARad(direccion(0));
    this->beta = gradARad(direccion(1));

    calculaPos();
}

void LuzDireccional::variarAnguloAlpha(float incremento){
    // De grados a radianes

    float inc = gradARad(incremento);

    alpha += inc;
    calculaPos();
}

void LuzDireccional::variarAnguloBeta(float incremento){
    // De grados a radianes

    float inc = gradARad(incremento);

    beta += inc;
    calculaPos();
}

void LuzDireccional::ajustaAngulos(){
    //0 <= aplha <= 2PI

    if(alpha > 2*M_PI)
        alpha -= 2*M_PI;
    if(alpha < 0.0)
        alpha += 2*M_PI;

    // 0 <= beta <= 2PI

    if(beta > 2*M_PI)
        beta -= 2*M_PI;
    if(beta < 0.0)
        beta += 2*M_PI;
}

float LuzDireccional::gradARad(float grad){
    return grad*M_PI/180.0;
}

void LuzDireccional::calculaPos(){
    //radio = 1
    // pasamos de coordenadas esféricas a cartesianas
    //  x = 1*sen(beta)*cos(alpha)
    //  y = 1*sen(beta)*sen(alpha)
    //  z = 1*cos(beta)

    ajustaAngulos();

    this->posicion = {sinf(this->beta)*cosf(this->alpha),
                    sinf(this->beta)*sinf(this->alpha),
                    cosf(this->beta),
                    0.0};
}