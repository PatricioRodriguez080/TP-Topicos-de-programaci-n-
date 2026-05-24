#include <stdio.h>
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

int guardarMatrizAuditMiembros(const char *path, const t_matriz_audit_miembros *m){
    FILE *fp = fopen(path, "wb");
    int i;
    if (!fp) return 0;
    for (i = 0; i < N_TIPOS_ERROR_MIEMBROS; i++){
        fwrite(&m->filas[i].cantidad, sizeof(unsigned), 1, fp);
        if (m->filas[i].cantidad > 0 && m->filas[i].dnis)
            fwrite(m->filas[i].dnis, sizeof(long), m->filas[i].cantidad, fp);
    }
    fclose(fp);
    return 1;
}

int cargarMatrizAuditMiembros(const char *path, t_matriz_audit_miembros *m){
    FILE *fp = fopen(path, "rb");
    int i;
    unsigned cant;
    if (!fp) return 0;
    for (i = 0; i < N_TIPOS_ERROR_MIEMBROS; i++){
        if (fread(&cant, sizeof(unsigned), 1, fp) != 1){
            fclose(fp);
            return 0;
        }
        if (cant > m->filas[i].capacidad){
            long *nv = realloc(m->filas[i].dnis, cant * sizeof(long));
            if (!nv){
                fclose(fp);
                return 0;
            }
            m->filas[i].dnis = nv;
            m->filas[i].capacidad = cant;
        }
        if (cant > 0 && fread(m->filas[i].dnis, sizeof(long), cant, fp) != cant){
            fclose(fp);
            return 0;
        }
        m->filas[i].cantidad = cant;
    }
    fclose(fp);
    return 1;
}
