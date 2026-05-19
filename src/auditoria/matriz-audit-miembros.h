#ifndef MATRIZ_AUDIT_MIEMBROS_H
#define MATRIZ_AUDIT_MIEMBROS_H

#define N_TIPOS_ERROR_MIEMBROS 11

typedef struct {
    long     *dnis;
    unsigned  cantidad;
    unsigned  capacidad;
} t_fila_audit_miembros;

typedef struct {
    t_fila_audit_miembros filas[N_TIPOS_ERROR_MIEMBROS];
} t_matriz_audit_miembros;

void crearMatrizAuditMiembros(t_matriz_audit_miembros *m);
void agregarMatrizAuditMiembros(t_matriz_audit_miembros *m,int codigoError, long dni);
void liberarMatrizAuditMiembros(t_matriz_audit_miembros *m);

#endif
