#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stddef.h>
#include "utils-fechas.h"

void armarNombreArchivo(char *out, size_t n, const char *base, t_fecha f, const char *ext);
int  existeArchivo(const char *path);

#endif
