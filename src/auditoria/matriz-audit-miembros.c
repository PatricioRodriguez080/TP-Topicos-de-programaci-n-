#include <stdlib.h>
#include "matriz-audit-miembros.h"

#define CAPACIDAD_INICIAL_FILA 10
#define FACTOR_CRECIMIENTO     1.3

void crearMatrizAuditMiembros(t_matriz_audit_miembros *m){
    int i;
    for (i = 0; i < N_TIPOS_ERROR_MIEMBROS; i++){
        m->filas[i].dnis = malloc(CAPACIDAD_INICIAL_FILA * sizeof(long));
        m->filas[i].cantidad = 0;
        m->filas[i].capacidad = CAPACIDAD_INICIAL_FILA;
    }
}

void agregarMatrizAuditMiembros(t_matriz_audit_miembros *m,int codigoError, long dni){
    int fila = codigoError - 1;
    t_fila_audit_miembros *f;

    if (fila < 0 || fila >= N_TIPOS_ERROR_MIEMBROS) return;

    f = &m->filas[fila];
    if (f->cantidad >= f->capacidad){
        f->capacidad = (unsigned)(f->capacidad * FACTOR_CRECIMIENTO) + 1;
        f->dnis = realloc(f->dnis, f->capacidad * sizeof(long));
    }
    f->dnis[f->cantidad++] = dni;
}

void liberarMatrizAuditMiembros(t_matriz_audit_miembros *m){
    int i;
    for (i = 0; i < N_TIPOS_ERROR_MIEMBROS; i++){
        free(m->filas[i].dnis);
        m->filas[i].dnis = NULL;
        m->filas[i].cantidad = 0;
        m->filas[i].capacidad = 0;
    }
}
