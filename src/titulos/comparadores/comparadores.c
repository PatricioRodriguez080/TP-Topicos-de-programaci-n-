#include "comparadores.h"
#include "../../indice/indice.h"
#include "../titulo.h"

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
