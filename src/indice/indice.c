#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "indice.h"

void indice_crear(t_indice *indice, size_t nmemb, size_t tamanyo){
    indice->vindice = malloc(nmemb * tamanyo);
    indice->cantidad_elementos_actual = 0;
    indice->cantidad_elementos_maxima = nmemb;
}

void indice_redimensionar(t_indice *indice, size_t nmemb, size_t tamanyo){
    indice->vindice = realloc(indice->vindice, nmemb * tamanyo);
    indice->cantidad_elementos_maxima = nmemb;
}

int indice_vacio(const t_indice *indice){
    return indice->cantidad_elementos_actual == 0 ? OK : ERROR;
}

int indice_lleno(const t_indice *indice){
    return indice->cantidad_elementos_actual >= indice->cantidad_elementos_maxima ? OK : ERROR;
}

void indice_vaciar(t_indice *indice){
    indice->cantidad_elementos_actual = 0;
}

int indice_insertar(t_indice *indice, const void *registro, size_t tamanyo,
                    int (*cmp)(const void *, const void *)){
    char *base;
    int pos;

    if (indice_lleno(indice))
        indice_redimensionar(indice,
            (size_t)(indice->cantidad_elementos_maxima * INCREMENTO), tamanyo);

    if (!indice->vindice) return ERROR;

    base = (char *) indice->vindice;
    pos = (int) indice->cantidad_elementos_actual;
    while (pos > 0 && cmp(base + (pos - 1) * tamanyo, registro) > 0)
        pos--;

    if ((unsigned)pos < indice->cantidad_elementos_actual)
        memmove(base + (pos + 1) * tamanyo,
                base + pos * tamanyo,
                (indice->cantidad_elementos_actual - pos) * tamanyo);

    memcpy(base + pos * tamanyo, registro, tamanyo);
    indice->cantidad_elementos_actual++;
    return OK;
}

int indice_eliminar(t_indice *indice, const void *registro, size_t tamanyo,
                    int (*cmp)(const void *, const void *)){
    /* TODO */
    return ERROR;
}

int indice_buscar(const t_indice *indice, const void *registro, size_t nmemb,
                  size_t tamanyo, int (*cmp)(const void *, const void *)){
    /* TODO */
    return NO_EXISTE;
}

int indice_cargar(const char *path, t_indice *indice, void *vreg_ind,
                  size_t tamanyo, int (*cmp)(const void *, const void *)){
    FILE *fp = fopen(path, "rb");
    if (!fp) return ERROR;

    while (fread(vreg_ind, tamanyo, 1, fp) == 1)
        indice_insertar(indice, vreg_ind, tamanyo, cmp);

    fclose(fp);
    return OK;
}
