#include <stdlib.h>
#include "matriz-audit-titulos.h"
#include "../validaciones/validaciones-titulos.h"

#define CAPACIDAD_INICIAL_FILA 10
#define FACTOR_CRECIMIENTO     1.3

void crearMatrizAuditTitulos(t_matriz_audit_titulos *m){
    int i;
    for (i = 0; i < N_TIPOS_ERROR_TITULOS; i++){
        m->filas[i].ids = malloc(CAPACIDAD_INICIAL_FILA * sizeof(int));
        m->filas[i].cantidad = 0;
        m->filas[i].capacidad = CAPACIDAD_INICIAL_FILA;
    }
}

void agregarMatrizAuditTitulos(t_matriz_audit_titulos *m,int codigoError, int idPelicula){
    int fila = codigoError - ERROR_ID_PELICULA;
    t_fila_audit_titulos *f;

    if (fila < 0 || fila >= N_TIPOS_ERROR_TITULOS) return;

    f = &m->filas[fila];
    if (f->cantidad >= f->capacidad){
        f->capacidad = (unsigned)(f->capacidad * FACTOR_CRECIMIENTO) + 1;
        f->ids = realloc(f->ids, f->capacidad * sizeof(int));
    }
    f->ids[f->cantidad++] = idPelicula;
}

void liberarMatrizAuditTitulos(t_matriz_audit_titulos *m){
    int i;
    for (i = 0; i < N_TIPOS_ERROR_TITULOS; i++){
        free(m->filas[i].ids);
        m->filas[i].ids = NULL;
        m->filas[i].cantidad = 0;
        m->filas[i].capacidad = 0;
    }
}
