#include "comparadores.h"
#include "../../indice/indice.h"
#include "../miembro.h"

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
