#include "material.h"

Material::Material(){
    this->ambiente = {0.2, 0.2, 0.2, 1.0};
    this->difuso = {0.8, 0.8, 0.8, 1.0};
    this->especular = {0.0, 0.0, 0.0, 1.0};
    this->brillo = 0*128;
}

Material::Material(Tupla4f ambiente, Tupla4f difuso, Tupla4f especular, float brillo){
    this->ambiente = ambiente;
    this->difuso = difuso;
    this->especular = especular;
    this->brillo = brillo;
}

void Material::aplicar(){
    glDisable(GL_COLOR_MATERIAL);
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
    
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
}