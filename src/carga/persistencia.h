#ifndef PERSISTENCIA_H_INCLUDED
#define PERSISTENCIA_H_INCLUDED

#include <stddef.h>
#include "../utils/utils-fechas.h"
#include "../indice/indice.h"

void armarNombreArchivo(char *out, size_t n,
                        const char *base, t_fecha f, const char *ext);
int  existeArchivo(const char *path);

int  cargarMiembrosDesdeBin(const char *path, t_indice *miembrosCompletos,
                            t_indice *exitoMiembros);
int  cargarTitulosDesdeBin (const char *path, t_indice *titulosCompletos,
                            t_indice *exitoTitulos);

int  guardarMiembros(const char *path, const t_indice *miembrosCompletos);
int  guardarTitulos (const char *path, const t_indice *titulosCompletos);

#endif
