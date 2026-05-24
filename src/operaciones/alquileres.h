#ifndef ALQUILERES_H_INCLUDED
#define ALQUILERES_H_INCLUDED

#include "../utils/utils-fechas.h"

typedef struct {
    long    dni;
    int     idPelicula;
    int     contador;
    int     activos;
    t_fecha fechaUltima;
} t_alquiler;

typedef struct {
    t_alquiler *v;
    unsigned    cantidad;
    unsigned    capacidad;
} t_alquileres;

void alquileres_crear(t_alquileres *a);
void alquileres_liberar(t_alquileres *a);
int  alquileres_buscar(const t_alquileres *a, long dni, int idPelicula);
int  alquileres_registrar(t_alquileres *a, long dni, int idPelicula, t_fecha fecha);
int  alquileres_contarActivosDeMiembro(const t_alquileres *a, long dni);
int  alquileres_guardar(const char *path, const t_alquileres *a);
int  alquileres_cargar(const char *path, t_alquileres *a);

#endif
