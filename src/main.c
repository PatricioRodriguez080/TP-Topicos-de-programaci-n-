#include <stdio.h>
#include <stdlib.h>
#include "utils/utils-fechas.h"
#include "carga/carga-miembros.h"

int main(){
    t_fecha fechaProceso;

    // Aca pedimos fecha proceso y la parseamos a t_fecha //

    cargaMiembros(fechaProceso);

    return 0;
}
