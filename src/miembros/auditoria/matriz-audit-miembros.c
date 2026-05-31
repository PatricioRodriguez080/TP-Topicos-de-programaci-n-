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

void mostrarMatrizAuditMiembros(t_matriz_audit_miembros *m){
    const char *nombresError[N_TIPOS_ERROR_MIEMBROS] = {
        "ERROR_DNI",
        "ERROR_SEXO",
        "ERROR_ESTADO",
        "ERROR_PLAN",
        "ERROR_CUIL",
        "ERROR_FECHA_NACIMIENTO",
        "ERROR_FECHA_AFILIACION",
        "ERROR_CATEGORIA",
        "ERROR_EMAIL_TUTOR",
        "ERROR_FECHA_ULTIMA_CUOTA",
        "ERROR_APELLIDO_NOMBRE"
    };
    int i, j;
    const t_fila_audit_miembros *f;

    printf("\n=== MATRIZ DE AUDITORIA - MIEMBROS ===\n");
    for (i = 0; i < N_TIPOS_ERROR_MIEMBROS; i++){
        f = &m->filas[i];
        printf("%-26s: ", nombresError[i]);
        if (f->cantidad == 0){
            printf("(sin errores)");
        } else {
            for (j = 0; j < f->cantidad; j++){
                printf("%ld ", f->dnis[j]);
            }
        }
        printf("  total: %u\n", f->cantidad);
    }
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
