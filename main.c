#include <stdio.h>
#include <stdlib.h>
#include "utils-fechas.h"
#include "carga-miembros.h"

int main(){
    t_fecha fechaProceso;

    // Aca pedimos fecha proceso y la parseamos a t_fecha //

    cargaMiembros(fechaProceso);

    return 0;
}
