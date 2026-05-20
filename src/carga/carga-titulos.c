#include <stdio.h>
#include "carga-titulos.h"
#include "preproc-titulos.h"
#include "../validaciones/validaciones-titulos.h"

#define ARCHIVO_TITULOS_CSV  "Archivos/titulos.csv"
#define ARCHIVO_TITULOS_BIN  "Archivos/titulos.bin"

static int cmpTitulosPorId(const void *a, const void *b){
    const Titulo *ta = a;
    const Titulo *tb = b;
    if (ta->idPelicula < tb->idPelicula) return -1;
    if (ta->idPelicula > tb->idPelicula) return 1;
    return 0;
}

static int cmpRegIndiceTituloPorId(const void *a, const void *b){
    const t_reg_indice_titulo *ra = a;
    const t_reg_indice_titulo *rb = b;
    if (ra->idPelicula < rb->idPelicula) return -1;
    if (ra->idPelicula > rb->idPelicula) return 1;
    return 0;
}

void cargaTitulos(t_indice *indiceExito,t_matriz_audit_titulos *audit){
    t_indice indiceRaw;
    Titulo buffer;
    Titulo *titulos;
    t_reg_indice_titulo reg;
    unsigned i;
    int resultado;

    csvATitulosBin(ARCHIVO_TITULOS_CSV, ARCHIVO_TITULOS_BIN);

    indice_crear(&indiceRaw, CANTIDAD_ELEMENTOS, sizeof(Titulo));
    indice_cargar(ARCHIVO_TITULOS_BIN, &indiceRaw, &buffer,
                  sizeof(Titulo), cmpTitulosPorId);

    titulos = (Titulo *) indiceRaw.vindice;
    for (i = 0; i < indiceRaw.cantidad_elementos_actual; i++){
        resultado = validarTitulo(titulos[i]);
        if (resultado == VALIDACION_OK){
            reg.idPelicula = titulos[i].idPelicula;
            reg.nro_reg = i;
            indice_insertar(indiceExito, &reg, sizeof(t_reg_indice_titulo),
                            cmpRegIndiceTituloPorId);
        } else {
            agregarMatrizAuditTitulos(audit, resultado, titulos[i].idPelicula);
        }
    }

    indice_vaciar(&indiceRaw);
}
