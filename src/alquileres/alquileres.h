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

void crearAlquileres(t_alquileres *a);
void liberarAlquileres(t_alquileres *a);
int  buscarAlquiler(const t_alquileres *a, long dni, int idPelicula);
int  registrarAlquiler(t_alquileres *a, long dni, int idPelicula, t_fecha fecha);
int  contarAlquileresActivosDeMiembro(const t_alquileres *a, long dni);
int  guardarAlquileres(const char *path, const t_alquileres *a);
int  cargarAlquileres(const char *path, t_alquileres *a);

#endif
