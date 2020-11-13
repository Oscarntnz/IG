#include "aux.h"
#include "cilindro.h"

Cilindro::Cilindro(){}


Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, 
const float radio, EnumEjes eje_r, bool con_tapas){
    perfil.clear();
    this->altura = altura;
    this->radio = radio;
    eje_rotacion = eje_r;
    tiene_tapas.first = true;
    tiene_tapas.second = true;

    int vert_perfil = num_vert_perfil;
    if(vert_perfil < 2) vert_perfil = 2;
    int instancias_perf = num_instancias_perf;
    if(instancias_perf < 2) instancias_perf = 2;

    float coordenada_variante = 0;

    if(eje_r == EnumEjes::E_X){
        perfil.push_back({-altura/2, 0.0, 0.0});
        
        for(int i = 0; i < vert_perfil; i++){
            coordenada_variante = -altura/2 + i*(altura/(vert_perfil-1));
            perfil.push_back({coordenada_variante, radio, 0.0});
        }

        perfil.push_back({altura/2, 0.0, 0.0});
    }
    else if(eje_r == EnumEjes::E_Y){
        perfil.push_back({0.0, -altura/2, 0.0});

        for(int i = 0; i < vert_perfil; i++){
            coordenada_variante = -altura/2 + i*(altura/(vert_perfil-1));
            perfil.push_back({radio, coordenada_variante, 0.0});
        }

        perfil.push_back({0.0, altura/2, 0.0});
    }
    else{
        perfil.push_back({0.0, 0.0, -altura/2});
        
        for(int i = 0; i < vert_perfil; i++){
            coordenada_variante = -altura/2 + i*(altura/(vert_perfil-1));
            perfil.push_back({0.0, radio, coordenada_variante});
        }

        perfil.push_back({0.0, 0.0, altura/2});
    }

    //crearPerfilDebug();
    crearMalla(perfil, instancias_perf, con_tapas);
}