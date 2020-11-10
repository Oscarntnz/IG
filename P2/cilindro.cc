#include "aux.h"
#include "cilindro.h"

Cilindro::Cilindro(){}


Cilindro::Cilindro(int num_vert_perfil, int num_instancias_perf, float h, float r){
    altura = h;
    radio = r;
    perfil.resize(4);

    perfil[0] = {0.0, -altura/2, 0.0}; perfil[1] = {radio, -altura/2, 0.0};
    perfil[2] = {radio, altura/2, 0.0}; perfil[3] = {0.0, altura/2, 0.0};

    tapas.first = true;
    tapas.second = true;

    crearMalla(perfil, num_instancias_perf);

    reserva_espacio();
    rellenar_v_colores();
}