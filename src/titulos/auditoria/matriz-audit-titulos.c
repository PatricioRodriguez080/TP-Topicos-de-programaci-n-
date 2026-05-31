#include <stdio.h>
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

void mostrarMatrizAuditTitulos(t_matriz_audit_titulos *m){
    const char *nombresError[N_TIPOS_ERROR_TITULOS] = {
        "ERROR_ID_PELICULA",
        "ERROR_TITULO",
        "ERROR_GENERO",
        "ERROR_STOCK",
        "ERROR_ESTADO_TITULO"
    };
    int i, j;
    const t_fila_audit_titulos *f;

    printf("\n=== MATRIZ DE AUDITORIA - TITULOS ===\n");
    for (i = 0; i < N_TIPOS_ERROR_TITULOS; i++){
        f = &m->filas[i];
        printf("%-26s: ", nombresError[i]);
        if (f->cantidad == 0){
            printf("(sin errores)");
        } else {
            for (j = 0; j < f->cantidad; j++){
                printf("%d ", f->ids[j]);
            }
        }
        printf("  total: %u\n", f->cantidad);
    }
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

int guardarMatrizAuditTitulos(const char *path, const t_matriz_audit_titulos *m){
    FILE *fp = fopen(path, "wb");
    int i;
    if (!fp) return 0;
    for (i = 0; i < N_TIPOS_ERROR_TITULOS; i++){
        fwrite(&m->filas[i].cantidad, sizeof(unsigned), 1, fp);
        if (m->filas[i].cantidad > 0 && m->filas[i].ids)
            fwrite(m->filas[i].ids, sizeof(int), m->filas[i].cantidad, fp);
    }
    fclose(fp);
    return 1;
}

int cargarMatrizAuditTitulos(const char *path, t_matriz_audit_titulos *m){
    FILE *fp = fopen(path, "rb");
    int i;
    unsigned cant;
    if (!fp) return 0;
    for (i = 0; i < N_TIPOS_ERROR_TITULOS; i++){
        if (fread(&cant, sizeof(unsigned), 1, fp) != 1){
            fclose(fp);
            return 0;
        }
        if (cant > m->filas[i].capacidad){
            int *nv = realloc(m->filas[i].ids, cant * sizeof(int));
            if (!nv){
                fclose(fp);
                return 0;
            }
            m->filas[i].ids = nv;
            m->filas[i].capacidad = cant;
        }
        if (cant > 0 && fread(m->filas[i].ids, sizeof(int), cant, fp) != cant){
            fclose(fp);
            return 0;
        }
        m->filas[i].cantidad = cant;
    }
    fclose(fp);
    return 1;
}
