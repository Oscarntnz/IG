#include "camara.h"
#include "aux.h"

float Camara::sensibilidad = 0.75;

Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float left, float right, float near, float far)
{
    this->eye = eye;
    this->at = at;
    this->up = up;

    this->tipo = tipo;

    this->left = left;
    this->right = right;
    this->near = near;
    this->far = far;

    this->eyeInicial = eye;
    this->atInicial = at;
    this->objSelec = -1;
}

void Camara::rotarXExaminar(float angle)
{
    Tupla3f v_dir = eye - at;
    angle *= GRAD_A_RAD;
    float mod = sqrtf(v_dir.lengthSq());

    v_dir(1) = cosf(angle) * v_dir(1) - sinf(angle) * v_dir(2);
    v_dir(2) = sinf(angle) * v_dir(1) + cosf(angle) * v_dir(2);

    eye = v_dir.normalized() * mod + at;
}

void Camara::rotarYExaminar(float angle)
{
    Tupla3f v_dir = eye - at;
    angle *= GRAD_A_RAD;
    float mod = sqrtf(v_dir.lengthSq());

    v_dir(0) = cosf(angle) * v_dir(0) + sinf(angle) * v_dir(2);
    v_dir(2) = -sinf(angle) * v_dir(0) + cosf(angle) * v_dir(2);

    eye = v_dir.normalized() * mod + at;
}

void Camara::rotarZExaminar(float angle)
{
    Tupla3f v_dir = eye - at;
    angle *= GRAD_A_RAD;
    float mod = sqrtf(v_dir.lengthSq());

    v_dir(0) = cosf(angle) * v_dir(0) - sinf(angle) * v_dir(1);
    v_dir(1) = sinf(angle) * v_dir(0) + cosf(angle) * v_dir(1);

    eye = v_dir.normalized() * mod + at;
}

void Camara::rotarXFirstPerson(float angle)
{
    Tupla3f v_dir = at - eye;
    angle *= GRAD_A_RAD;
    float mod = sqrtf(v_dir.lengthSq());

    v_dir(1) = cosf(angle) * v_dir(1) - sinf(angle) * v_dir(2);
    v_dir(2) = sinf(angle) * v_dir(1) + cosf(angle) * v_dir(2);

    at = v_dir.normalized() * mod + eye;
}

void Camara::rotarYFirstPerson(float angle)
{
    Tupla3f v_dir = at - eye;
    angle *= GRAD_A_RAD;
    float mod = sqrtf(v_dir.lengthSq());

    v_dir(0) = cosf(angle) * v_dir(0) + sinf(angle) * v_dir(2);
    v_dir(2) = -sinf(angle) * v_dir(0) + cosf(angle) * v_dir(2);

    at = v_dir.normalized() * mod + eye;
}

void Camara::rotarZFirstPerson(float angle)
{
    Tupla3f v_dir = at - eye;
    angle *= GRAD_A_RAD;
    float mod = sqrtf(v_dir.lengthSq());

    v_dir(0) = cosf(angle) * v_dir(0) - sinf(angle) * v_dir(1);
    v_dir(1) = sinf(angle) * v_dir(0) + cosf(angle) * v_dir(1);

    at = v_dir.normalized() * mod + eye;
}

void Camara::mover(float x, float y, float z)
{
    Tupla3f suma = {x, y, z};

    at = at + suma;
    eye = eye + suma;
}

void Camara::zoom(float factor)
{
    // Modifico el FOV

    left *= factor;
    right *= factor;
}

void Camara::setObserver()
{
    gluLookAt(eye(0), eye(1), eye(2), at(0), at(1), at(2), up(0), up(1), up(2));
}

void Camara::setProyeccion(const float aspectRatio)
{
    float bottom = -(((-left + right)) / aspectRatio) / 2,
          top = (((-left + right)) / aspectRatio) / 2;

    if (tipo == TipoCamara::ORTOGONAL)
        glOrtho(left, right, bottom, top, near, far);
    else
        glFrustum(left, right, bottom, top, near, far);
}

void Camara::girar(int x, int y)
{
    x *= sensibilidad;
    y *= sensibilidad;

    if (objSelec == -1)
    {
        rotarXFirstPerson(-y);
        rotarYFirstPerson(-x);
    }
    else
    {
        rotarXExaminar(y);
        rotarYExaminar(x);
    }
}