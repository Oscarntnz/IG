#include "aux.h"
#include "cono.h"

Cono::Cono(float altura, float radio, int num_instancias, bool tapa_i, EnumEjes eje_r){
    perfil.resize(3);

    if(eje_r = EnumEjes::E_X){
        perfil[0] = {-altura/2, 0.0, 0.0}; perfil[1] = {-altura/2, -radio, 0.0};
        perfil[2] = {altura/2, 0.0, 0.0};
    }
    else if(eje_r = EnumEjes::E_Y){
        perfil[0] = {0.0, -altura/2, 0.0}; perfil[1] = {radio, -altura/2, 0.0};
        perfil[2] = {0.0, altura/2, 0.0};
    }
    else{
        perfil[0] = {0.0, 0.0, -altura/2}; perfil[1] = {radio, 0.0, -altura/2};
        perfil[2] = {0.0, 0.0, 0.0};
    }

    tapas.first = true;
    tapas.second = /*tapa_i*/ false;
    eje_rotacion = eje_r;

    crearMalla(perfil, num_instancias);

    reserva_espacio();
    rellenar_v_colores();
}