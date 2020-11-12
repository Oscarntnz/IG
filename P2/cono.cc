#include "aux.h"
#include "cono.h"

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio, EnumEjes eje_r, bool tapa_inf){
    perfil.clear();
    this->altura = altura;
    this->radio = radio;
    tapas.first = tapa_inf;
    tapas.second = false;
    eje_rotacion = eje_r;

    float coordenada_variante_1 = 0,
    coordenada_variante_2 = 0;

    if(eje_r == EnumEjes::E_X){
        if(tapas.first) perfil.push_back({-altura/2, 0.0, 0.0});

        for(int i = 0; i < num_vert_perfil; i++){
            coordenada_variante_1 = -altura/2 + i*(altura/(num_vert_perfil-1));
            coordenada_variante_2 = radio - i*(radio/(num_vert_perfil-1));
            perfil.push_back({coordenada_variante_1, coordenada_variante_2, 0.0});
        }
    }
    else if(eje_r == EnumEjes::E_Y){
        if(tapas.first) perfil.push_back({0.0, -altura/2, 0.0});

        for(int i = 0; i < num_vert_perfil; i++){
            coordenada_variante_1 = -altura/2 + i*(altura/(num_vert_perfil-1));
            coordenada_variante_2 = radio - i*(radio/(num_vert_perfil-1));
            perfil.push_back({coordenada_variante_2, coordenada_variante_1, 0.0});
        }
    }
    else{
        if(tapas.first) perfil.push_back({0.0, 0.0, -altura/2});

        for(int i = 0; i < num_vert_perfil; i++){
            coordenada_variante_1 = -altura/2 + i*(altura/(num_vert_perfil-1));
            coordenada_variante_2 = radio - i*(radio/(num_vert_perfil-1));
            perfil.push_back({coordenada_variante_2, 0.0, coordenada_variante_1});
        }
    }

    //crearPerfilDebug();
    crearMalla(perfil, num_instancias_perf, (tapas.first && tapas.second));
}