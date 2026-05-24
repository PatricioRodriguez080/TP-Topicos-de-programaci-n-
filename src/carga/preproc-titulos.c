#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preproc-titulos.h"
#include "comparadores.h"
#include "../indice/indice.h"
#include "../validaciones/validaciones-titulos.h"

static int parsearLineaCSV(char *linea, Titulo *t){
    char *token;
    char *rest = linea;

    linea[strcspn(linea, "\r\n")] = '\0';

    token = strtok_r(rest, ";", &rest); if (!token) return ERROR;
    t->idPelicula = atoi(token);

    token = strtok_r(NULL, ";", &rest); if (!token) return ERROR;
    strncpy(t->titulo, token, sizeof(t->titulo) - 1);
    t->titulo[sizeof(t->titulo) - 1] = '\0';

    token = strtok_r(NULL, ";", &rest); if (!token) return ERROR;
    strncpy(t->genero, token, sizeof(t->genero) - 1);
    t->genero[sizeof(t->genero) - 1] = '\0';

    token = strtok_r(NULL, ";", &rest); if (!token) return ERROR;
    t->stock = atoi(token);

    t->estado = 'A';

    return OK;
}

void csvATitulosBin(const char *csvPath, const char *binPath){
    FILE *fpCsv;
    FILE *fpBin;
    t_indice indiceTmp;
    char linea[256];
    Titulo t;
    Titulo *titulos;
    unsigned i;

    fpCsv = fopen(csvPath, "r");
    if (!fpCsv) return;

    indice_crear(&indiceTmp, CANTIDAD_ELEMENTOS, sizeof(Titulo));

    while (fgets(linea, sizeof(linea), fpCsv) != NULL){
        if (parsearLineaCSV(linea, &t) == OK){
            indice_insertar(&indiceTmp, &t, sizeof(Titulo), cmpTitulosPorId);
        }
    }
    fclose(fpCsv);

    fpBin = fopen(binPath, "wb");
    if (!fpBin){
        indice_vaciar(&indiceTmp);
        return;
    }

    titulos = (Titulo *) indiceTmp.vindice;
    for (i = 0; i < indiceTmp.cantidad_elementos_actual; i++){
        fwrite(&titulos[i], sizeof(Titulo), 1, fpBin);
    }
    fclose(fpBin);

    indice_vaciar(&indiceTmp);
}
