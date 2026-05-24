#include <stdio.h>
#include <stdlib.h>
#include "utils/utils-fechas.h"
#include "carga/carga-miembros.h"
#include "carga/carga-titulos.h"
#include "carga/persistencia.h"
#include "indice/indice.h"
#include "validaciones/validaciones-miembros.h"
#include "validaciones/validaciones-titulos.h"
#include "auditoria/matriz-audit-miembros.h"
#include "auditoria/matriz-audit-titulos.h"
#include "menu/menu.h"
#include "operaciones/alquileres.h"

int main(){
    t_fecha fechaProceso = pedirFechaProceso();
    t_indice indiceExitoMiembros;
    t_indice indiceExitoTitulos;
    t_indice miembrosCompletos;
    t_indice titulosCompletos;
    t_matriz_audit_miembros auditMiembros;
    t_matriz_audit_titulos  auditTitulos;
    t_alquileres alquileres;
    t_contexto_menu ctx;
    char pathMiembros[128], pathTitulos[128], pathAlquileres[128];
    char pathAuditMiembros[128], pathAuditTitulos[128];

    indice_crear(&indiceExitoMiembros, CANTIDAD_ELEMENTOS, sizeof(t_reg_indice));
    indice_crear(&indiceExitoTitulos,  CANTIDAD_ELEMENTOS, sizeof(t_reg_indice_titulo));
    indice_crear(&miembrosCompletos,   CANTIDAD_ELEMENTOS, sizeof(Miembro));
    indice_crear(&titulosCompletos,    CANTIDAD_ELEMENTOS, sizeof(Titulo));
    alquileres_crear(&alquileres);
    crearMatrizAuditMiembros(&auditMiembros);
    crearMatrizAuditTitulos (&auditTitulos);

    armarNombreArchivo(pathMiembros,   sizeof(pathMiembros),
                       "Archivos/miembros",   fechaProceso, "bin");
    armarNombreArchivo(pathTitulos,    sizeof(pathTitulos),
                       "Archivos/titulos",    fechaProceso, "bin");
    armarNombreArchivo(pathAlquileres, sizeof(pathAlquileres),
                       "Archivos/alquileres", fechaProceso, "bin");
    armarNombreArchivo(pathAuditMiembros, sizeof(pathAuditMiembros),
                       "Archivos/audit_miembros", fechaProceso, "bin");
    armarNombreArchivo(pathAuditTitulos,  sizeof(pathAuditTitulos),
                       "Archivos/audit_titulos",  fechaProceso, "bin");

    if (existeArchivo(pathMiembros) && existeArchivo(pathTitulos)){
        cargarMiembrosDesdeBin(pathMiembros, &miembrosCompletos, &indiceExitoMiembros);
        cargarTitulosDesdeBin (pathTitulos,  &titulosCompletos,  &indiceExitoTitulos);
        if (existeArchivo(pathAlquileres))
            alquileres_cargar(pathAlquileres, &alquileres);
        if (existeArchivo(pathAuditMiembros))
            cargarMatrizAuditMiembros(pathAuditMiembros, &auditMiembros);
        if (existeArchivo(pathAuditTitulos))
            cargarMatrizAuditTitulos(pathAuditTitulos, &auditTitulos);
    } else {
        cargaMiembros(&indiceExitoMiembros, &miembrosCompletos, &auditMiembros, fechaProceso);
        cargaTitulos (&indiceExitoTitulos,  &titulosCompletos,  &auditTitulos);
    }

    ctx.exitoMiembros     = &indiceExitoMiembros;
    ctx.exitoTitulos      = &indiceExitoTitulos;
    ctx.miembrosCompletos = &miembrosCompletos;
    ctx.titulosCompletos  = &titulosCompletos;
    ctx.auditMiembros     = &auditMiembros;
    ctx.auditTitulos      = &auditTitulos;
    ctx.fechaProceso      = fechaProceso;
    ctx.alquileres        = &alquileres;

    mostrarMenu(&ctx);

    guardarMiembros  (pathMiembros,    &miembrosCompletos);
    guardarTitulos   (pathTitulos,     &titulosCompletos);
    alquileres_guardar(pathAlquileres, &alquileres);
    guardarMatrizAuditMiembros(pathAuditMiembros, &auditMiembros);
    guardarMatrizAuditTitulos (pathAuditTitulos,  &auditTitulos);

    indice_liberar(&indiceExitoMiembros);
    indice_liberar(&indiceExitoTitulos);
    indice_liberar(&miembrosCompletos);
    indice_liberar(&titulosCompletos);
    alquileres_liberar(&alquileres);
    liberarMatrizAuditMiembros(&auditMiembros);
    liberarMatrizAuditTitulos (&auditTitulos);

    return 0;
}
