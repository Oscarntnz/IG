#include "aux.h"
#include "cono.h"

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, 
const float radio, EnumEjes eje_r, bool con_tapa){
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

    float coordenada_variante_1 = 0,
    coordenada_variante_2 = 0;

    if(eje_r == EnumEjes::E_X){
        perfil.push_back({-altura/2, 0.0, 0.0});

        for(int i = 0; i < vert_perfil; i++){
            coordenada_variante_1 = -altura/2 + i*(altura/(vert_perfil-1));
            coordenada_variante_2 = radio - i*(radio/(vert_perfil-1));
            perfil.push_back({coordenada_variante_1, coordenada_variante_2, 0.0});
        }
    }
    else if(eje_r == EnumEjes::E_Y){
        perfil.push_back({0.0, -altura/2, 0.0});

        for(int i = 0; i < vert_perfil; i++){
            coordenada_variante_1 = -altura/2 + i*(altura/(vert_perfil-1));
            coordenada_variante_2 = radio - i*(radio/(vert_perfil-1));
            perfil.push_back({coordenada_variante_2, coordenada_variante_1, 0.0});
        }
    }
    else{
        perfil.push_back({0.0, 0.0, -altura/2});

        for(int i = 0; i < vert_perfil; i++){
            coordenada_variante_1 = -altura/2 + i*(altura/(vert_perfil-1));
            coordenada_variante_2 = radio - i*(radio/(vert_perfil-1));
            perfil.push_back({coordenada_variante_2, 0.0, coordenada_variante_1});
        }
    }

    //crearPerfilDebug();
    crearMalla(perfil, num_instancias_perf, con_tapa);
}