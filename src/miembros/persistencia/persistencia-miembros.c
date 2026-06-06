#include <stdio.h>
#include "persistencia-miembros.h"
#include "../comparadores/comparadores.h"
#include "../miembro.h"
#include "../validaciones/validaciones-miembros.h"

int cargarMiembrosDesdeBin(const char *path, t_indice *miembrosCompletos, t_indice *exitoMiembros, t_fecha fechaProceso){
    FILE *fp = fopen(path, "rb");
    Miembro m;
    t_reg_indice reg;

    if (!fp) return 0;
    while (fread(&m, sizeof(Miembro), 1, fp) == 1){
        indice_insertar(miembrosCompletos, &m, sizeof(Miembro), cmpMiembrosPorDni);
        if (m.estado != 'B' && validarMiembro(m, fechaProceso) == VALIDACION_OK){
            reg.dni = m.dni;
            reg.nro_reg = miembrosCompletos->cantidad_elementos_actual - 1;
            if (indice_buscar(exitoMiembros, &reg, exitoMiembros->cantidad_elementos_actual, sizeof(t_reg_indice), cmpRegIndicePorDni) == NO_EXISTE)
                indice_insertar(exitoMiembros, &reg, sizeof(t_reg_indice), cmpRegIndicePorDni);
        }
    }
    fclose(fp);
    return 1;
}

int guardarMiembros(const char *path, const t_indice *miembrosCompletos){
    FILE *fp = fopen(path, "wb");

    if (!fp) return 0;
    fwrite(miembrosCompletos->vindice, sizeof(Miembro), miembrosCompletos->cantidad_elementos_actual, fp);
    fclose(fp);
    return 1;
}
