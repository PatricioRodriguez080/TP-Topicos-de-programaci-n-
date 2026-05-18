#ifndef UTILS_VALIDACIONES_H
#define UTILS_VALIDACIONES_H

#define VALIDACION_OK 0

typedef int (*ValidadorFn)(void *dato);

int ejecutarValidacion(void *dato, ValidadorFn funcion);

#endif
