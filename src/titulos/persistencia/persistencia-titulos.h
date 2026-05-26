#ifndef PERSISTENCIA_TITULOS_H_INCLUDED
#define PERSISTENCIA_TITULOS_H_INCLUDED

#include "../../indice/indice.h"

int cargarTitulosDesdeBin(const char *path, t_indice *titulosCompletos, t_indice *exitoTitulos);
int guardarTitulos(const char *path, const t_indice *titulosCompletos);

#endif
