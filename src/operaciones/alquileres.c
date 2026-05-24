#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alquileres.h"

#define ALQ_CAP_INICIAL 32

void alquileres_crear(t_alquileres *a){
    a->v = (t_alquiler *) malloc(ALQ_CAP_INICIAL * sizeof(t_alquiler));
    a->cantidad = 0;
    a->capacidad = a->v ? ALQ_CAP_INICIAL : 0;
}

void alquileres_liberar(t_alquileres *a){
    if (!a) return;
    free(a->v);
    a->v = NULL;
    a->cantidad = 0;
    a->capacidad = 0;
}

int alquileres_buscar(const t_alquileres *a, long dni, int idPelicula){
    unsigned i;
    for (i = 0; i < a->cantidad; i++)
        if (a->v[i].dni == dni && a->v[i].idPelicula == idPelicula)
            return (int) i;
    return -1;
}

static int alquileres_redimensionar(t_alquileres *a){
    unsigned nueva = a->capacidad ? (unsigned)(a->capacidad * 1.5) : ALQ_CAP_INICIAL;
    t_alquiler *nv = (t_alquiler *) realloc(a->v, nueva * sizeof(t_alquiler));
    if (!nv) return 0;
    a->v = nv;
    a->capacidad = nueva;
    return 1;
}

int alquileres_registrar(t_alquileres *a, long dni, int idPelicula, t_fecha fecha){
    int pos = alquileres_buscar(a, dni, idPelicula);
    if (pos >= 0){
        a->v[pos].contador++;
        a->v[pos].activos++;
        a->v[pos].fechaUltima = fecha;
        return 1;
    }
    if (a->cantidad >= a->capacidad && !alquileres_redimensionar(a)) return 0;
    a->v[a->cantidad].dni = dni;
    a->v[a->cantidad].idPelicula = idPelicula;
    a->v[a->cantidad].contador = 1;
    a->v[a->cantidad].activos = 1;
    a->v[a->cantidad].fechaUltima = fecha;
    a->cantidad++;
    return 1;
}

int alquileres_contarActivosDeMiembro(const t_alquileres *a, long dni){
    unsigned i;
    int total = 0;
    for (i = 0; i < a->cantidad; i++)
        if (a->v[i].dni == dni) total += a->v[i].activos;
    return total;
}

int alquileres_guardar(const char *path, const t_alquileres *a){
    FILE *fp = fopen(path, "wb");
    if (!fp) return 0;
    fwrite(a->v, sizeof(t_alquiler), a->cantidad, fp);
    fclose(fp);
    return 1;
}

int alquileres_cargar(const char *path, t_alquileres *a){
    FILE *fp = fopen(path, "rb");
    t_alquiler tmp;
    if (!fp) return 0;
    while (fread(&tmp, sizeof(t_alquiler), 1, fp) == 1){
        if (a->cantidad >= a->capacidad && !alquileres_redimensionar(a)){
            fclose(fp);
            return 0;
        }
        a->v[a->cantidad++] = tmp;
    }
    fclose(fp);
    return 1;
}
