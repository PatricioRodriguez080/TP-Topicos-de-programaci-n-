#include <string.h>
#include <ctype.h>
#include "validaciones-titulos.h"

int validarIdPelicula(void *dato){
    DatosValidacionTitulo *d = (DatosValidacionTitulo *)dato;
    // Nos queda tener en cuenta que debe ser unico //
    if (d->titulo->idPelicula <= 0)
        return ERROR_ID_PELICULA;
    return VALIDACION_OK;
}

char *normalizarTitulo(char *cad){
    char *lect = cad, *esc = cad;
    int primeraLetraPalabra;
    int posicionPalabra = 0;

    while (*lect){
        while (*lect && isspace((unsigned char)*lect))
            lect++;

        if (*lect){
            posicionPalabra++;
            if (posicionPalabra > 1){
                *esc = ' ';
                esc++;
            }
            primeraLetraPalabra = 1;
            while (*lect && !isspace((unsigned char)*lect)){
                *esc = primeraLetraPalabra ? toupper((unsigned char)*lect) : tolower((unsigned char)*lect);
                primeraLetraPalabra = 0;
                esc++;
                lect++;
            }
        }
    }

    *esc = '\0';
    return cad;
}

int validarNombreTitulo(void *dato){
    DatosValidacionTitulo *d = (DatosValidacionTitulo *)dato;
    char esperado[60];

    strcpy(esperado, d->titulo->titulo);
    normalizarTitulo(esperado);
    if (strcmp(d->titulo->titulo, esperado) != 0)
        return ERROR_TITULO;
    return VALIDACION_OK;
}

int validarGenero(void *dato){
    DatosValidacionTitulo *d = (DatosValidacionTitulo *)dato;

    if (strcmp(d->titulo->genero, "Accion")  != 0 &&
        strcmp(d->titulo->genero, "Drama")   != 0 &&
        strcmp(d->titulo->genero, "Comedia") != 0 &&
        strcmp(d->titulo->genero, "Terror")  != 0)
        return ERROR_GENERO;
    return VALIDACION_OK;
}

int validarStock(void *dato){
    DatosValidacionTitulo *d = (DatosValidacionTitulo *)dato;

    if (d->titulo->stock < 1)
        return ERROR_STOCK;
    return VALIDACION_OK;
}

int validarEstadoTitulo(void *dato){
    DatosValidacionTitulo *d = (DatosValidacionTitulo *)dato;

    if (d->titulo->estado != 'A' && d->titulo->estado != 'B')
        return ERROR_ESTADO_TITULO;
    return VALIDACION_OK;
}

int validarTitulo(Titulo titulo){
    DatosValidacionTitulo datos;
    datos.titulo = &titulo;

    ValidadorFn validaciones[] = {
        validarIdPelicula,
        validarNombreTitulo,
        validarGenero,
        validarStock,
        validarEstadoTitulo
    };

    int cantidad = sizeof(validaciones) / sizeof(validaciones[0]);
    int i, res;

    for (i = 0; i < cantidad; i++){
        res = ejecutarValidacion(&datos, validaciones[i]);
        if (res != VALIDACION_OK) return res;
    }

    return VALIDACION_OK;
}
