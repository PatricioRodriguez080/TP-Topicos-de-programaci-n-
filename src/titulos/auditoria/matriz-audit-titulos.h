#ifndef MATRIZ_AUDIT_TITULOS_H
#define MATRIZ_AUDIT_TITULOS_H

#define N_TIPOS_ERROR_TITULOS 5

typedef struct {
    int      *ids;
    unsigned  cantidad;
    unsigned  capacidad;
} t_fila_audit_titulos;

typedef struct {
    t_fila_audit_titulos filas[N_TIPOS_ERROR_TITULOS];
} t_matriz_audit_titulos;

void crearMatrizAuditTitulos(t_matriz_audit_titulos *m);
void agregarMatrizAuditTitulos(t_matriz_audit_titulos *m,int codigoError, int idPelicula);
void liberarMatrizAuditTitulos(t_matriz_audit_titulos *m);
int  guardarMatrizAuditTitulos(const char *path, const t_matriz_audit_titulos *m);
int  cargarMatrizAuditTitulos (const char *path, t_matriz_audit_titulos *m);

#endif
