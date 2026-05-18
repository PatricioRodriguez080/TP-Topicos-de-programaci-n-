#ifndef VALIDACIONES_TITULOS_H
#define VALIDACIONES_TITULOS_H

#include "utils-validaciones.h"

#define ERROR_ID_PELICULA  12
#define ERROR_TITULO       13
#define ERROR_GENERO       14
#define ERROR_STOCK        15

typedef struct {
    int  idPelicula;
    char titulo[60];
    char genero[20];
    int  stock;
} Titulo;

typedef struct {
    Titulo *titulo;
} DatosValidacionTitulo;

int validarIdPelicula(void *dato);
int validarNombreTitulo(void *dato);
int validarGenero(void *dato);
int validarStock(void *dato);

int validarTitulo(Titulo titulo);

#endif
