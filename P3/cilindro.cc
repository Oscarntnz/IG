#include "aux.h"
#include "cilindro.h"

Cilindro::Cilindro(){}


Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, 
const float radio, EnumEjes eje_r, bool tapa_inf, bool tapa_sup){
    perfil.clear();
    this->altura = altura;
    this->radio = radio;
    tapas.first = tapa_inf;
    tapas.second = tapa_sup;
    eje_rotacion = eje_r;

    float coordenada_variante = 0;

    if(eje_r == EnumEjes::E_X){
        if(tapas.first) perfil.push_back({-altura/2, 0.0, 0.0});
        
        for(int i = 0; i < num_vert_perfil; i++){
            coordenada_variante = -altura/2 + i*(altura/(num_vert_perfil-1));
            perfil.push_back({coordenada_variante, radio, 0.0});
        }

        if(tapas.second) perfil.push_back({altura/2, 0.0, 0.0});
    }
    else if(eje_r == EnumEjes::E_Y){
        if(tapas.first) perfil.push_back({0.0, -altura/2, 0.0});

        for(int i = 0; i < num_vert_perfil; i++){
            coordenada_variante = -altura/2 + i*(altura/(num_vert_perfil-1));
            perfil.push_back({radio, coordenada_variante, 0.0});
        }

        if(tapas.second) perfil.push_back({0.0, altura/2, 0.0});
    }
    else{
        if(tapas.first) perfil.push_back({0.0, 0.0, -altura/2});
        
        for(int i = 0; i < num_vert_perfil; i++){
            coordenada_variante = -altura/2 + i*(altura/(num_vert_perfil-1));
            perfil.push_back({0.0, radio, coordenada_variante});
        }

        if(tapas.second) perfil.push_back({0.0, 0.0, altura/2});
    }

    //crearPerfilDebug();
    crearMalla(perfil, num_instancias_perf, (tapas.first || tapas.second));
}