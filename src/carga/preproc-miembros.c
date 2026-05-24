#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "preproc-miembros.h"
#include "comparadores.h"
#include "../indice/indice.h"
#include "../validaciones/validaciones-miembros.h"
#include "../utils/utils-fechas.h"

static int parsearLineaCSV(char *linea, Miembro *m){
    char *token;
    char *rest = linea;

    linea[strcspn(linea, "\r\n")] = '\0';

    token = strtok_r(rest, ";", &rest); if (!token) return ERROR;
    m->dni = atol(token);

    token = strtok_r(NULL, ";", &rest); if (!token) return ERROR;
    strncpy(m->cuil, token, sizeof(m->cuil) - 1);
    m->cuil[sizeof(m->cuil) - 1] = '\0';

    token = strtok_r(NULL, ";", &rest); if (!token) return ERROR;
    strncpy(m->apellidoNombre, token, sizeof(m->apellidoNombre) - 1);
    m->apellidoNombre[sizeof(m->apellidoNombre) - 1] = '\0';

    token = strtok_r(NULL, ";", &rest); if (!token) return ERROR;
    if (!parsearFecha(token, &m->fechaNacimiento)) return ERROR;

    token = strtok_r(NULL, ";", &rest); if (!token) return ERROR;
    m->sexo = token[0];

    token = strtok_r(NULL, ";", &rest); if (!token) return ERROR;
    if (!parsearFecha(token, &m->fechaAfiliacion)) return ERROR;

    token = strtok_r(NULL, ";", &rest); if (!token) return ERROR;
    strncpy(m->categoria, token, sizeof(m->categoria) - 1);
    m->categoria[sizeof(m->categoria) - 1] = '\0';

    token = strtok_r(NULL, ";", &rest); if (!token) return ERROR;
    if (!parsearFecha(token, &m->fechaUltimaCuota)) return ERROR;

    token = strtok_r(NULL, ";", &rest); if (!token) return ERROR;
    m->estado = token[0];

    token = strtok_r(NULL, ";", &rest); if (!token) return ERROR;
    strncpy(m->plan, token, sizeof(m->plan) - 1);
    m->plan[sizeof(m->plan) - 1] = '\0';

    token = strtok_r(NULL, ";", &rest);
    if (token){
        strncpy(m->emailTutor, token, sizeof(m->emailTutor) - 1);
        m->emailTutor[sizeof(m->emailTutor) - 1] = '\0';
    } else {
        m->emailTutor[0] = '\0';
    }

    return OK;
}

void csvAMiembrosBin(const char *csvPath, const char *binPath){
    FILE *fpCsv;
    FILE *fpBin;
    t_indice indiceTmp;
    char linea[256];
    Miembro m;
    Miembro *miembros;
    unsigned i;

    fpCsv = fopen(csvPath, "r");
    if (!fpCsv) return;

    indice_crear(&indiceTmp, CANTIDAD_ELEMENTOS, sizeof(Miembro));

    while (fgets(linea, sizeof(linea), fpCsv) != NULL){
        if (parsearLineaCSV(linea, &m) == OK){
            indice_insertar(&indiceTmp, &m, sizeof(Miembro), cmpMiembrosPorDni);
        }
    }
    fclose(fpCsv);

    fpBin = fopen(binPath, "wb");
    if (!fpBin){
        indice_vaciar(&indiceTmp);
        return;
    }

    miembros = (Miembro *) indiceTmp.vindice;
    for (i = 0; i < indiceTmp.cantidad_elementos_actual; i++){
        fwrite(&miembros[i], sizeof(Miembro), 1, fpBin);
    }
    fclose(fpBin);

    indice_vaciar(&indiceTmp);
}
