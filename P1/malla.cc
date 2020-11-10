#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void Malla3D::draw_ModoInmediato()
{

   // visualizar la malla usando glDrawElements,

   // habilitar uso de un array de vértices y de colores
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   // indicar el formato y la dirección de memoria del array de vértices
   // (son tuplas de 3 valores float, sin espacio entre ellas)
   glVertexPointer(3, GL_FLOAT, 0, v.data());
   glColorPointer(3, GL_FLOAT, 0, c_i.data());

   glPointSize(5.0);

   // visualizar, indicando: tipo de primitiva, número de índices,
   // tipo de los índices, y dirección de la tabla de índices
   
   if(modos_visualizacion[ModoVisualizacion::SOLIDO]){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      dibuja(f);
   }
   if(modos_visualizacion[ModoVisualizacion::PUNTOS]){
      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      glColorPointer(3, GL_FLOAT, 0, c_p.data());
      dibuja(f);
   }
   if(modos_visualizacion[ModoVisualizacion::LINEAS]){
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glColorPointer(3, GL_FLOAT, 0, c_l.data());
      dibuja(f);
   }
   if(modos_visualizacion[ModoVisualizacion::AJEDREZ]){
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glColorPointer(3, GL_FLOAT, 0, c_a.data());
      dibuja(a);
      glColorPointer(3, GL_FLOAT, 0, c_a_2.data());
      dibuja(a_2);
   }
   
   // deshabilitar array de vértices
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido()
{
   if(id_vbo_ver == 0)
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*3*sizeof(Tupla3f), v.data());
   if(id_vbo_tri == 0)
      id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, f.size()*sizeof(Tupla3i), f.data());
   if(id_vbo_aj1 == 0)
      id_vbo_aj1 = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, a.size()*sizeof(Tupla3i), a.data());
   if(id_vbo_aj2 == 0)
      id_vbo_aj2 = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, a_2.size()*sizeof(Tupla3i), a_2.data());
   if(id_vbo_col == 0)
      id_vbo_col = CrearVBO(GL_ARRAY_BUFFER, c_d.size()*sizeof(Tupla3f), c_d.data());
   if(id_vbo_pun == 0)
      id_vbo_pun = CrearVBO(GL_ARRAY_BUFFER, c_p.size()*sizeof(Tupla3f), c_p.data());
   if(id_vbo_lin == 0)
      id_vbo_lin = CrearVBO(GL_ARRAY_BUFFER, c_l.size()*sizeof(Tupla3f), c_l.data());
   if(id_vbo_ca1 == 0)
      id_vbo_ca1 = CrearVBO(GL_ARRAY_BUFFER, c_a.size()*sizeof(Tupla3f), c_a.data());
   if(id_vbo_ca2 == 0)
      id_vbo_ca2 = CrearVBO(GL_ARRAY_BUFFER, c_a_2.size()*sizeof(Tupla3f), c_a_2.data());

   // especificar localización y formato de la tabla de vértices, habilitar tabla

   glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ver);   // activar VBO de vértices
   glVertexPointer(3, GL_FLOAT, 0, 0);          // especifica formato y offset (=0)
   glBindBuffer(GL_ARRAY_BUFFER , 0);          // desactivar VBO de vértices.
   glEnableClientState(GL_VERTEX_ARRAY);        // habilitar tabla de vértices

   glPointSize(5.0);

   // especificar localización y formato de la tabla de colores, habilitar tabla

   if(modos_visualizacion[ModoVisualizacion::SOLIDO]){
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col);   // activar VBO de colores
      glColorPointer(3, GL_FLOAT, 0, 0);          // especifica formato y offset (=0)
      glBindBuffer(GL_ARRAY_BUFFER , 0);          // desactivar VBO de colores.
      glEnableClientState(GL_COLOR_ARRAY);        // activar tabla de colores

      // visualizar triángulos con glDrawElements (puntero a tabla == 0)

      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      dibuja_dif(f, id_vbo_tri);
   }
   if(modos_visualizacion[ModoVisualizacion::PUNTOS]){

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_pun);   // activar VBO de colores
      glColorPointer(3, GL_FLOAT, 0, 0);          // especifica formato y offset (=0)
      glBindBuffer(GL_ARRAY_BUFFER , 0);          // desactivar VBO de colores.
      glEnableClientState(GL_COLOR_ARRAY);        // activar tabla de colores

      // visualizar triángulos con glDrawElements (puntero a tabla == 0)

      glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
      dibuja_dif(f, id_vbo_tri);
   }
   if(modos_visualizacion[ModoVisualizacion::LINEAS]){
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_lin);   // activar VBO de colores
      glColorPointer(3, GL_FLOAT, 0, 0);          // especifica formato y offset (=0)
      glBindBuffer(GL_ARRAY_BUFFER , 0);          // desactivar VBO de colores.
      glEnableClientState(GL_COLOR_ARRAY);        // activar tabla de colores

      // visualizar triángulos con glDrawElements (puntero a tabla == 0)

      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      dibuja_dif(f, id_vbo_tri);
   }

   if(modos_visualizacion[ModoVisualizacion::AJEDREZ]){
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ca1);   // activar VBO de colores
      glColorPointer(3, GL_FLOAT, 0, 0);          // especifica formato y offset (=0)
      glBindBuffer(GL_ARRAY_BUFFER , 0);          // desactivar VBO de colores.
      glEnableClientState(GL_COLOR_ARRAY);        // activar tabla de colores

      // visualizar triángulos con glDrawElements (puntero a tabla == 0)

      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      dibuja_dif(f, id_vbo_aj1);

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_ca2);   // activar VBO de colores
      glColorPointer(3, GL_FLOAT, 0, 0);          // especifica formato y offset (=0)
      glBindBuffer(GL_ARRAY_BUFFER , 0);          // desactivar VBO de colores.

      // visualizar triángulos con glDrawElements (puntero a tabla == 0)

      dibuja_dif(f, id_vbo_aj2);
   }

   // desactivar uso de array de vértices
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_COLOR_ARRAY);
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void Malla3D::draw()
{
   // completar .....(práctica 1)
   if(modo_dibujo == ModoDibujado::INMEDIATO)
      draw_ModoInmediato();
   else if(modo_dibujo == ModoDibujado::DIFERIDO)
      draw_ModoDiferido();
}

GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram)
{
   GLuint id_vbo;                // resultado: identificador de VBO
   glGenBuffers(1, & id_vbo);   // crear nuevo VBO, obtener identificador (nunca 0)

   glBindBuffer(tipo_vbo , id_vbo ); // activar el VBO usando su identificador

   // esta instrucción hace la transferencia de datos desde RAM hacia GPU
   glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);

   glBindBuffer (tipo_vbo, 0);      // desactivación del VBO (activar 0)
   return id_vbo ;                  // devolver el identificador resultado
}

void Malla3D::dibuja(std::vector<Tupla3i> v){
   glDrawElements(GL_TRIANGLES, v.size()*3, GL_UNSIGNED_INT, v.data());
}

void Malla3D::dibuja_dif(std::vector<Tupla3i> v, GLuint id){
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);    // activar VBO de triángulos
   glDrawElements(GL_TRIANGLES, 3*f.size (), GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , 0);    
}

void Malla3D::cambiar_visualizacion(ModoVisualizacion modo){
      if(modo != AJEDREZ){
         modos_visualizacion[AJEDREZ] = false;
         modos_visualizacion[modo] = !modos_visualizacion[modo];
      }
      else{
         modos_visualizacion[PUNTOS] = false;
         modos_visualizacion[LINEAS] = false;
         modos_visualizacion[SOLIDO] = false;
         modos_visualizacion[modo] = !modos_visualizacion[modo];
      }
}

void Malla3D::mover(Tupla3f vector_despl){
   for(auto it = v.begin(); it != v.end(); ++it)
      *it = *it + vector_despl;
}