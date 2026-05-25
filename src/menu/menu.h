#ifndef MENU_H
#define MENU_H

#include "../indice/indice.h"
#include "../utils/utils-fechas.h"
#include "../miembros/auditoria/matriz-audit-miembros.h"
#include "../titulos/auditoria/matriz-audit-titulos.h"
#include "../alquileres/alquileres.h"

typedef struct {
    t_indice *exitoMiembros;
    t_indice *exitoTitulos;
    t_indice *miembrosCompletos;
    t_indice *titulosCompletos;
    t_matriz_audit_miembros *auditMiembros;
    t_matriz_audit_titulos *auditTitulos;
    t_fecha fechaProceso;
    t_alquileres *alquileres;
} t_contexto_menu;

void mostrarMenu(t_contexto_menu *ctx);

#endif
