#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "persistencia.h"
#include "comparadores.h"
#include "../validaciones/validaciones-miembros.h"
#include "../validaciones/validaciones-titulos.h"

void armarNombreArchivo(char *out, size_t n,
                        const char *base, t_fecha f, const char *ext){
    snprintf(out, n, "%s_%04d%02d%02d.%s", base, f.anio, f.mes, f.dia, ext);
}

int existeArchivo(const char *path){
    FILE *fp = fopen(path, "rb");
    if (!fp) return 0;
    fclose(fp);
    return 1;
}

int cargarMiembrosDesdeBin(const char *path, t_indice *miembrosCompletos,
                           t_indice *exitoMiembros){
    FILE *fp = fopen(path, "rb");
    Miembro m;
    t_reg_indice reg;
    if (!fp) return 0;
    while (fread(&m, sizeof(Miembro), 1, fp) == 1){
        indice_insertar(miembrosCompletos, &m, sizeof(Miembro), cmpMiembrosPorDni);
        if (m.estado != 'B'){
            reg.dni = m.dni;
            reg.nro_reg = miembrosCompletos->cantidad_elementos_actual - 1;
            indice_insertar(exitoMiembros, &reg,
                            sizeof(t_reg_indice), cmpRegIndicePorDni);
        }
    }
    fclose(fp);
    return 1;
}

int cargarTitulosDesdeBin(const char *path, t_indice *titulosCompletos,
                          t_indice *exitoTitulos){
    FILE *fp = fopen(path, "rb");
    Titulo t;
    t_reg_indice_titulo reg;
    if (!fp) return 0;
    while (fread(&t, sizeof(Titulo), 1, fp) == 1){
        indice_insertar(titulosCompletos, &t, sizeof(Titulo), cmpTitulosPorId);
        if (t.estado != 'B'){
            reg.idPelicula = t.idPelicula;
            reg.nro_reg = titulosCompletos->cantidad_elementos_actual - 1;
            indice_insertar(exitoTitulos, &reg,
                            sizeof(t_reg_indice_titulo), cmpRegIndiceTituloPorId);
        }
    }
    fclose(fp);
    return 1;
}

int guardarMiembros(const char *path, const t_indice *miembrosCompletos){
    FILE *fp = fopen(path, "wb");
    if (!fp) return 0;
    fwrite(miembrosCompletos->vindice, sizeof(Miembro),
           miembrosCompletos->cantidad_elementos_actual, fp);
    fclose(fp);
    return 1;
}

int guardarTitulos(const char *path, const t_indice *titulosCompletos){
    FILE *fp = fopen(path, "wb");
    if (!fp) return 0;
    fwrite(titulosCompletos->vindice, sizeof(Titulo),
           titulosCompletos->cantidad_elementos_actual, fp);
    fclose(fp);
    return 1;
}
