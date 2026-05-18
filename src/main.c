#include <stdio.h>
#include <stdlib.h>
#include "utils/utils-fechas.h"
#include "carga/carga-miembros.h"
#include "indice/indice.h"
#include "validaciones/validaciones-miembros.h"

int main(){
    t_fecha fechaProceso = {16, 5, 2026};
    t_indice indiceExito;

    // Aca pedimos fecha proceso y la parseamos a t_fecha //

    indice_crear(&indiceExito, CANTIDAD_ELEMENTOS, sizeof(Miembro));
    cargaMiembros(&indiceExito, fechaProceso);

    return 0;
}
