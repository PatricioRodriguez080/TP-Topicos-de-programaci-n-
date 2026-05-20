#include <stdio.h>
#include <stdlib.h>
#include "utils/utils-fechas.h"
#include "carga/carga-miembros.h"
#include "carga/carga-titulos.h"
#include "indice/indice.h"
#include "validaciones/validaciones-miembros.h"
#include "auditoria/matriz-audit-miembros.h"
#include "auditoria/matriz-audit-titulos.h"
#include "menu/menu.h"

int main(){
    t_fecha fechaProceso = pedirFechaProceso();
    t_indice indiceExitoMiembros;
    t_indice indiceExitoTitulos;
    t_matriz_audit_miembros auditMiembros;
    t_matriz_audit_titulos  auditTitulos;
    t_contexto_menu ctx;

    indice_crear(&indiceExitoMiembros, CANTIDAD_ELEMENTOS, sizeof(t_reg_indice));
    indice_crear(&indiceExitoTitulos,  CANTIDAD_ELEMENTOS, sizeof(t_reg_indice_titulo));

    crearMatrizAuditMiembros(&auditMiembros);
    crearMatrizAuditTitulos(&auditTitulos);

    cargaMiembros(&indiceExitoMiembros, &auditMiembros, fechaProceso);
    cargaTitulos(&indiceExitoTitulos,  &auditTitulos);

    ctx.exitoMiembros = &indiceExitoMiembros;
    ctx.exitoTitulos  = &indiceExitoTitulos;
    ctx.auditMiembros = &auditMiembros;
    ctx.auditTitulos  = &auditTitulos;
    ctx.fechaProceso  = fechaProceso;

    mostrarMenu(&ctx);

    liberarMatrizAuditMiembros(&auditMiembros);
    liberarMatrizAuditTitulos(&auditTitulos);

    return 0;
}
