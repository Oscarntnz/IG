#include "aux.h"
#include "jarron.h"

Jarron::Jarron(int num_instancias, bool con_tapas){
    eje_rotacion = EnumEjes::E_Y;
    tiene_tapas.first = true;
    tiene_tapas.second = false;

    perfil.clear();
    perfil.push_back({1, -1, 0});
    perfil.push_back({2, 0, 0});
    perfil.push_back({1, 1, 0});
    perfil.push_back({2, 2, 0});

    crearMalla(perfil, num_instancias, con_tapas);

    ObjRevolucion::setTextura("vase");
}