#include "comparadores.h"
#include "../indice/indice.h"
#include "../validaciones/validaciones-miembros.h"
#include "../validaciones/validaciones-titulos.h"

int cmpMiembrosPorDni(const void *a, const void *b){
    long da = ((const Miembro *)a)->dni;
    long db = ((const Miembro *)b)->dni;
    return (da > db) - (da < db);
}

int cmpRegIndicePorDni(const void *a, const void *b){
    long da = ((const t_reg_indice *)a)->dni;
    long db = ((const t_reg_indice *)b)->dni;
    return (da > db) - (da < db);
}

int cmpTitulosPorId(const void *a, const void *b){
    int ia = ((const Titulo *)a)->idPelicula;
    int ib = ((const Titulo *)b)->idPelicula;
    return (ia > ib) - (ia < ib);
}

int cmpRegIndiceTituloPorId(const void *a, const void *b){
    int ia = ((const t_reg_indice_titulo *)a)->idPelicula;
    int ib = ((const t_reg_indice_titulo *)b)->idPelicula;
    return (ia > ib) - (ia < ib);
}
