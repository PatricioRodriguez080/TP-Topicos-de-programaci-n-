#ifndef CARGA_MIEMBROS_H
#define CARGA_MIEMBROS_H

#include "../../utils/utils-fechas.h"
#include "../../indice/indice.h"
#include "../auditoria/matriz-audit-miembros.h"

void cargaMiembros(t_indice *indiceExito, t_indice *miembrosCompletos, t_matriz_audit_miembros *audit, t_fecha fechaProceso);

#endif
