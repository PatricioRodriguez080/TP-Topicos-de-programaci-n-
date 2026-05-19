#include <stdio.h>
#include <stdlib.h>
#include "utils/utils-fechas.h"
#include "carga/carga-miembros.h"
#include "carga/carga-titulos.h"
#include "indice/indice.h"
#include "validaciones/validaciones-miembros.h"

int main(){
    t_fecha fechaProceso = {16, 5, 2026};
    t_indice indiceExitoMiembros;
    t_indice indiceExitoTitulos;

    // Aca pedimos fecha proceso y la parseamos a t_fecha //

    indice_crear(&indiceExitoMiembros, CANTIDAD_ELEMENTOS, sizeof(t_reg_indice));
    indice_crear(&indiceExitoTitulos,  CANTIDAD_ELEMENTOS, sizeof(t_reg_indice_titulo));

    cargaMiembros(&indiceExitoMiembros, fechaProceso);
    cargaTitulos(&indiceExitoTitulos);

    return 0;
}
