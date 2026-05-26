#ifndef PERSISTENCIA_MIEMBROS_H_INCLUDED
#define PERSISTENCIA_MIEMBROS_H_INCLUDED

#include "../../indice/indice.h"

int cargarMiembrosDesdeBin(const char *path, t_indice *miembrosCompletos, t_indice *exitoMiembros);
int guardarMiembros(const char *path, const t_indice *miembrosCompletos);

#endif
