#include "esfera.h"

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio, 
EnumEjes eje_r, bool tapa_inf, bool tapa_sup){
    perfil.clear();
    this->radio = radio;
    tapas.first = tapa_inf;
    tapas.second = tapa_sup;
    eje_rotacion = eje_r;
    float f_rotacion = 0;
    int num_vert_con_polos = num_vert_perfil + 2;
    Tupla3f polo_s, polo_i;

    if(eje_r == EnumEjes::E_X){
        polo_i = {-radio, 0.0, 0.0};
        polo_s = {radio, 0.0, 0.0};
    }
    else if(eje_r == EnumEjes::E_Y){
        polo_i = {0.0, -radio, 0.0};
        polo_s = {0.0, radio, 0.0};
    }
    else{
        polo_i = {0.0, 0.0, -radio};
        polo_s = {0.0, 0.0, radio};
    }

    if(tapas.first) perfil.push_back(polo_i);

    for(int i = 1; i < num_vert_con_polos - 1; i++){
            f_rotacion = (M_PI*i)/(num_vert_con_polos-1);
            perfil.push_back(calcularPuntoPerfilRotado(f_rotacion, polo_i));
    }

    if(tapas.second) perfil.push_back(polo_s);

    //crearPerfilDebug();
    crearMalla(perfil, num_instancias_perf, (tapas.first && tapas.second));
}

Tupla3f Esfera::calcularPuntoPerfilRotado(float factor_rotacion, Tupla3f polo){
    Tupla3f salida = {0.0, 0.0, 0.0},
    puntoPartida = polo;

    if(eje_rotacion == EnumEjes::E_X || eje_rotacion == EnumEjes::E_Z){
        // Rota sobre el eje Y
        salida(EnumEjes::E_X) = puntoPartida(EnumEjes::E_X)*cos(factor_rotacion) + puntoPartida(EnumEjes::E_Z)*sin(factor_rotacion);
        salida(EnumEjes::E_Y) = puntoPartida(EnumEjes::E_Y);
        salida(EnumEjes::E_Z) = puntoPartida(EnumEjes::E_X)*-sin(factor_rotacion) + puntoPartida(EnumEjes::E_Z)*cos(factor_rotacion);
    }
    else if(eje_rotacion == EnumEjes::E_Y){
        // Rota sobre el eje Z
        salida(EnumEjes::E_X) = puntoPartida(EnumEjes::E_X)*cos(factor_rotacion) + puntoPartida(EnumEjes::E_Y)*-sin(factor_rotacion);
        salida(EnumEjes::E_Y) = puntoPartida(EnumEjes::E_X)*sin(factor_rotacion) + puntoPartida(EnumEjes::E_Y)*cos(factor_rotacion);
        salida(EnumEjes::E_Z) = puntoPartida(EnumEjes::E_Z);
    }

    return salida;
}