#ifndef CAMARA_H_
#define CAMARA_H_

#include "aux.h"

enum TipoCamara : int {ORTOGONAL = 0, PERSPECTIVA = 1};

class Camara
{
private:
    static float sensibilidad;
    Tupla3f eye;
    Tupla3f at;
    Tupla3f up;
    int tipo;                     // ORTOGONAL o Perspectiva
    float left, right, near, far; // o bien aspect, fov, near, far
    int objSelec;
    Tupla3f atInicial, eyeInicial;

public:
    Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float left, float right, float near, float far); // con los parametros necesarios
    void rotarXExaminar(float angle);
    void rotarYExaminar(float angle);
    void rotarZExaminar(float angle);
    void rotarXFirstPerson(float angle);
    void rotarYFirstPerson(float angle);
    void rotarZFirstPerson(float angle);
    void mover(float x, float y, float z);
    void zoom(float factor);
    void setObserver();
    void setProyeccion(const float aspectRatio);
    void girar(int x, int y);

    inline void setObjSelec(int objSelec){
        this->objSelec = objSelec;
    }

    inline const int getObjSelec() const{
        return this->objSelec;
    }

    inline const int getTipo() const{
        return tipo;
    }

    inline void setAt(Tupla3f at){
        this->at = at;
    }

    inline void resetAt(){
        this->at = atInicial;
    }

    inline void setEye(Tupla3f eye){
        this->eye = eye;
    }

    inline void resetEye(){
        this->eye = eyeInicial;
    }

    inline const Tupla3f getAt()const{
        return at;
    }

    inline const Tupla3f getEye()const{
        return eye;
    }
    inline void setSensibilidad(float sensibilidad){
        this->sensibilidad = sensibilidad;
    }
};

#endif