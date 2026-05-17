#include <stdio.h>
#include "carga-miembros.h"
#include "validaciones-miembros.h"
#include "indice.h"

#define ARCHIVO_MIEMBROS  "Archivos/miembros.csv"

static int cmpMiembrosPorDni(const void *a, const void *b){
    const Miembro *ma = a;
    const Miembro *mb = b;
    if (ma->dni < mb->dni) return -1;
    if (ma->dni > mb->dni) return 1;
    return 0;
}

void cargaMiembros(t_indice *indiceExito, t_fecha fechaProceso){
    t_indice indiceRaw;
    Miembro buffer;
    Miembro *miembros;
    unsigned i;
    int resultado;

    indice_crear(&indiceRaw, CANTIDAD_ELEMENTOS, sizeof(Miembro));
    indice_cargar(ARCHIVO_MIEMBROS, &indiceRaw, &buffer, sizeof(Miembro), cmpMiembrosPorDni);

    miembros = (Miembro *) indiceRaw.vindice;
    for (i = 0; i < indiceRaw.cantidad_elementos_actual; i++){
        resultado = validarMiembro(miembros[i], fechaProceso);
        if (resultado == VALIDACION_OK){
            indice_insertar(indiceExito, &miembros[i], sizeof(Miembro), cmpMiembrosPorDni);
        }
        // cuando agreguemos el indice de auditoria, insertar aca el miembro con su codigo de error //
    }

    indice_vaciar(&indiceRaw);
}
