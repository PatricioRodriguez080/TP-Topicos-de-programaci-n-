#include <stdio.h>
#include <stdlib.h>
#include "utils/utils-fechas.h"
#include "miembros/carga/carga-miembros.h"
#include "titulos/carga/carga-titulos.h"
#include "utils/persistencia.h"
#include "indice/indice.h"
#include "miembros/validaciones/validaciones-miembros.h"
#include "titulos/validaciones/validaciones-titulos.h"
#include "miembros/auditoria/matriz-audit-miembros.h"
#include "titulos/auditoria/matriz-audit-titulos.h"
#include "menu/menu.h"
#include "alquileres/alquileres.h"

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
    indice_crear(&indiceExitoTitulos, CANTIDAD_ELEMENTOS, sizeof(t_reg_indice_titulo));
    indice_crear(&miembrosCompletos, CANTIDAD_ELEMENTOS, sizeof(Miembro));
    indice_crear(&titulosCompletos, CANTIDAD_ELEMENTOS, sizeof(Titulo));
    crearAlquileres(&alquileres);
    crearMatrizAuditMiembros(&auditMiembros);
    crearMatrizAuditTitulos (&auditTitulos);

    armarNombreArchivo(pathMiembros, sizeof(pathMiembros), "Archivos/miembros", fechaProceso, "bin");
    armarNombreArchivo(pathTitulos, sizeof(pathTitulos), "Archivos/titulos",    fechaProceso, "bin");
    armarNombreArchivo(pathAlquileres, sizeof(pathAlquileres), "Archivos/alquileres", fechaProceso, "bin");
    armarNombreArchivo(pathAuditMiembros, sizeof(pathAuditMiembros), "Archivos/audit_miembros", fechaProceso, "bin");
    armarNombreArchivo(pathAuditTitulos, sizeof(pathAuditTitulos), "Archivos/audit_titulos",  fechaProceso, "bin");

    if (existeArchivo(pathMiembros) && existeArchivo(pathTitulos)){
        cargarMiembrosDesdeBin(pathMiembros, &miembrosCompletos, &indiceExitoMiembros);
        cargarTitulosDesdeBin (pathTitulos,  &titulosCompletos,  &indiceExitoTitulos);
        if (existeArchivo(pathAlquileres))
            cargarAlquileres(pathAlquileres, &alquileres);
        if (existeArchivo(pathAuditMiembros))
            cargarMatrizAuditMiembros(pathAuditMiembros, &auditMiembros);
        if (existeArchivo(pathAuditTitulos))
            cargarMatrizAuditTitulos(pathAuditTitulos, &auditTitulos);
    } else {
        cargaMiembros(&indiceExitoMiembros, &miembrosCompletos, &auditMiembros, fechaProceso);
        cargaTitulos (&indiceExitoTitulos,  &titulosCompletos,  &auditTitulos);
    }

    ctx.exitoMiembros = &indiceExitoMiembros;
    ctx.exitoTitulos = &indiceExitoTitulos;
    ctx.miembrosCompletos = &miembrosCompletos;
    ctx.titulosCompletos = &titulosCompletos;
    ctx.auditMiembros = &auditMiembros;
    ctx.auditTitulos = &auditTitulos;
    ctx.fechaProceso= fechaProceso;
    ctx.alquileres = &alquileres;

    mostrarMenu(&ctx);

    guardarMiembros(pathMiembros, &miembrosCompletos);
    guardarTitulos(pathTitulos, &titulosCompletos);
    guardarAlquileres(pathAlquileres, &alquileres);
    guardarMatrizAuditMiembros(pathAuditMiembros, &auditMiembros);
    guardarMatrizAuditTitulos(pathAuditTitulos,  &auditTitulos);

    indice_liberar(&indiceExitoMiembros);
    indice_liberar(&indiceExitoTitulos);
    indice_liberar(&miembrosCompletos);
    indice_liberar(&titulosCompletos);
    liberarAlquileres(&alquileres);
    liberarMatrizAuditMiembros(&auditMiembros);
    liberarMatrizAuditTitulos (&auditTitulos);

    return 0;
}
