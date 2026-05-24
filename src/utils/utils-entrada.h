#ifndef UTILS_ENTRADA_H_INCLUDED
#define UTILS_ENTRADA_H_INCLUDED

#include <stddef.h>
#include "utils-fechas.h"

int leerLineaTrim(const char *prompt, char *buf, size_t n);
int leerLong (const char *prompt, long *out);
int leerInt  (const char *prompt, int  *out);
int leerChar (const char *prompt, char *out);
int leerFecha(const char *prompt, t_fecha *out);
int pedirConfirmacion(const char *prompt);

#endif
