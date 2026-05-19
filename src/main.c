#include <stdio.h>
#include <stdlib.h>
#include "utils/utils-fechas.h"
#include "carga/carga-miembros.h"
#include "carga/carga-titulos.h"
#include "indice/indice.h"
#include "validaciones/validaciones-miembros.h"
#include "auditoria/matriz-audit-miembros.h"
#include "auditoria/matriz-audit-titulos.h"

int main(){
    t_fecha fechaProceso = {16, 5, 2026};
    t_indice indiceExitoMiembros;
    t_indice indiceExitoTitulos;
    t_matriz_audit_miembros auditMiembros;
    t_matriz_audit_titulos  auditTitulos;

    // Aca pedimos fecha proceso y la parseamos a t_fecha //

    indice_crear(&indiceExitoMiembros, CANTIDAD_ELEMENTOS, sizeof(t_reg_indice));
    indice_crear(&indiceExitoTitulos,  CANTIDAD_ELEMENTOS, sizeof(t_reg_indice_titulo));

    crearMatrizAuditMiembros(&auditMiembros);
    crearMatrizAuditTitulos(&auditTitulos);

    cargaMiembros(&indiceExitoMiembros, &auditMiembros, fechaProceso);
    cargaTitulos(&indiceExitoTitulos,  &auditTitulos);

    // aca deberia de ir el menu entiendo, no creo haber visto que se mencione el hecho de mostrar auditoria de errores //

    liberarMatrizAuditMiembros(&auditMiembros);
    liberarMatrizAuditTitulos(&auditTitulos);

    return 0;
}
