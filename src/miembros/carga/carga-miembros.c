#include <stdio.h>
#include "carga-miembros.h"
#include "preproc-miembros.h"
#include "../comparadores/comparadores.h"
#include "../validaciones/validaciones-miembros.h"

#define ARCHIVO_MIEMBROS_CSV  "Archivos/miembros.csv"
#define ARCHIVO_MIEMBROS_BIN  "Archivos/miembros.bin"

void cargaMiembros(t_indice *indiceExito, t_indice *miembrosCompletos, t_matriz_audit_miembros *audit, t_fecha fechaProceso){
    Miembro buffer;
    Miembro *miembros;
    t_reg_indice reg;
    unsigned i;
    int resultado;

    csvAMiembrosBin(ARCHIVO_MIEMBROS_CSV, ARCHIVO_MIEMBROS_BIN);

    indice_cargar(ARCHIVO_MIEMBROS_BIN, miembrosCompletos, &buffer, sizeof(Miembro), cmpMiembrosPorDni);

    miembros = (Miembro *) miembrosCompletos->vindice;
    for (i = 0; i < miembrosCompletos->cantidad_elementos_actual; i++){
        resultado = validarMiembro(miembros[i], fechaProceso);
        if (resultado == VALIDACION_OK){
            reg.dni = miembros[i].dni;
            reg.nro_reg = i;
            indice_insertar(indiceExito, &reg, sizeof(t_reg_indice), cmpRegIndicePorDni);
        } else {
            agregarMatrizAuditMiembros(audit, resultado, miembros[i].dni);
        }
    }
}
