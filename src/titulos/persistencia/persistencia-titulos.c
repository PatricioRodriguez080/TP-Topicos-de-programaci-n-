#include <stdio.h>
#include "persistencia-titulos.h"
#include "../comparadores/comparadores.h"
#include "../titulo.h"
#include "../validaciones/validaciones-titulos.h"

int cargarTitulosDesdeBin(const char *path, t_indice *titulosCompletos, t_indice *exitoTitulos){
    FILE *fp = fopen(path, "rb");
    Titulo t;
    t_reg_indice_titulo reg;

    if (!fp) return 0;
    while (fread(&t, sizeof(Titulo), 1, fp) == 1){
        indice_insertar(titulosCompletos, &t, sizeof(Titulo), cmpTitulosPorId);
        if (t.estado != 'B' && validarTitulo(t) == VALIDACION_OK){
            reg.idPelicula = t.idPelicula;
            reg.nro_reg = titulosCompletos->cantidad_elementos_actual - 1;
            if (indice_buscar(exitoTitulos, &reg, exitoTitulos->cantidad_elementos_actual, sizeof(t_reg_indice_titulo), cmpRegIndiceTituloPorId) == NO_EXISTE)
                indice_insertar(exitoTitulos, &reg, sizeof(t_reg_indice_titulo), cmpRegIndiceTituloPorId);
        }
    }
    fclose(fp);
    return 1;
}

int guardarTitulos(const char *path, const t_indice *titulosCompletos){
    FILE *fp = fopen(path, "wb");

    if (!fp) return 0;
    fwrite(titulosCompletos->vindice, sizeof(Titulo), titulosCompletos->cantidad_elementos_actual, fp);
    fclose(fp);
    return 1;
}
