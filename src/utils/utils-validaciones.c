#include "utils-validaciones.h"

int ejecutarValidacion(void *dato, ValidadorFn funcion){
    return funcion(dato);
}
