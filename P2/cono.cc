#include "aux.h"
#include "cono.h"

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio, EnumEjes eje_r){
    perfil.clear();
    this->altura = altura;
    this->radio = radio;
    tapas.first = (num_vert_perfil > 2? true : false);
    tapas.second = false;
    eje_rotacion = eje_r;

    if(eje_r == EnumEjes::E_X){
        if(tapas.first) perfil.push_back({-altura/2, 0.0, 0.0});
        perfil.push_back({-altura/2, radio, 0.0});
        perfil.push_back({altura/2, 0.0, 0.0});
    }
    else if(eje_r == EnumEjes::E_Y){
        if(tapas.first) perfil.push_back({0.0, -altura/2, 0.0});
        perfil.push_back({radio, -altura/2, 0.0});
        perfil.push_back({0.0, altura/2, 0.0});
    }
    else{
        if(tapas.first) perfil.push_back({0.0, 0.0, -altura/2});
        perfil.push_back({radio, 0.0, -altura/2});
        perfil.push_back({0.0, 0.0, altura/2});
    }

    crearMalla(perfil, num_instancias_perf);

    rellenar_v_ajedrez();
    rellenar_v_colores();
}