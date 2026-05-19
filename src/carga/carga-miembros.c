#include <stdio.h>
#include "carga-miembros.h"
#include "preproc-miembros.h"
#include "../validaciones/validaciones-miembros.h"

#define ARCHIVO_MIEMBROS_CSV  "Archivos/miembros.csv"
#define ARCHIVO_MIEMBROS_BIN  "Archivos/miembros.bin"

static int cmpMiembrosPorDni(const void *a, const void *b){
    const Miembro *ma = a;
    const Miembro *mb = b;
    if (ma->dni < mb->dni) return -1;
    if (ma->dni > mb->dni) return 1;
    return 0;
}

static int cmpRegIndicePorDni(const void *a, const void *b){
    const t_reg_indice *ra = a;
    const t_reg_indice *rb = b;
    if (ra->dni < rb->dni) return -1;
    if (ra->dni > rb->dni) return 1;
    return 0;
}

void cargaMiembros(t_indice *indiceExito, t_fecha fechaProceso){
    t_indice indiceRaw;
    Miembro buffer;
    Miembro *miembros;
    t_reg_indice reg;
    unsigned i;
    int resultado;

    csvAMiembrosBin(ARCHIVO_MIEMBROS_CSV, ARCHIVO_MIEMBROS_BIN);

    indice_crear(&indiceRaw, CANTIDAD_ELEMENTOS, sizeof(Miembro));
    indice_cargar(ARCHIVO_MIEMBROS_BIN, &indiceRaw, &buffer,
                  sizeof(Miembro), cmpMiembrosPorDni);

    miembros = (Miembro *) indiceRaw.vindice;
    for (i = 0; i < indiceRaw.cantidad_elementos_actual; i++){
        resultado = validarMiembro(miembros[i], fechaProceso);
        if (resultado == VALIDACION_OK){
            reg.dni = miembros[i].dni;
            reg.nro_reg = i;
            indice_insertar(indiceExito, &reg, sizeof(t_reg_indice),
                            cmpRegIndicePorDni);
        }
        // cuando agreguemos el indice de auditoria, insertar aca el miembro con su codigo de error //
    }

    indice_vaciar(&indiceRaw);
}
