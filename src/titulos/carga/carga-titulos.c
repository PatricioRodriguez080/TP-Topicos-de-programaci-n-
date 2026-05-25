#include <stdio.h>
#include "carga-titulos.h"
#include "preproc-titulos.h"
#include "../comparadores/comparadores.h"
#include "../validaciones/validaciones-titulos.h"

#define ARCHIVO_TITULOS_CSV  "Archivos/titulos.csv"
#define ARCHIVO_TITULOS_BIN  "Archivos/titulos.bin"

void cargaTitulos(t_indice *indiceExito, t_indice *titulosCompletos,t_matriz_audit_titulos *audit){
    Titulo buffer;
    Titulo *titulos;
    t_reg_indice_titulo reg;
    unsigned i;
    int resultado;

    csvATitulosBin(ARCHIVO_TITULOS_CSV, ARCHIVO_TITULOS_BIN);

    indice_cargar(ARCHIVO_TITULOS_BIN, titulosCompletos, &buffer, sizeof(Titulo), cmpTitulosPorId);

    titulos = (Titulo *) titulosCompletos->vindice;
    for (i = 0; i < titulosCompletos->cantidad_elementos_actual; i++){
        resultado = validarTitulo(titulos[i]);
        if (resultado == VALIDACION_OK){
            reg.idPelicula = titulos[i].idPelicula;
            reg.nro_reg = i;
            indice_insertar(indiceExito, &reg, sizeof(t_reg_indice_titulo), cmpRegIndiceTituloPorId);
        } else {
            agregarMatrizAuditTitulos(audit, resultado, titulos[i].idPelicula);
        }
    }
}
