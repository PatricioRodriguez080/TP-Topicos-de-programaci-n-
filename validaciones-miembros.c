#include <stdio.h>
#include <string.h>
#include "validaciones-miembros.h"

int validarDNI(long dni)
{
    if (dni <= 1000000 || dni >= 100000000){
        return ERROR_DNI;
    }
    return VALIDACION_OK;
}

int validarSexo(char sexo)
{
    if (sexo != 'F' && sexo != 'M' && sexo != 'O'){
        return ERROR_SEXO;
    }
    return VALIDACION_OK;
}

int validarEstado(char estado)
{
    if (estado != 'A' && estado != 'B'){
        return ERROR_ESTADO;
    }
    return VALIDACION_OK;
}

int validarPlan(const char *plan)
{
    if (strcmp(plan, "BASIC")   != 0 &&
        strcmp(plan, "PREMIUM") != 0 &&
        strcmp(plan, "VIP")     != 0 &&
        strcmp(plan, "FAMILY")  != 0){
            return ERROR_PLAN;
        }
    return VALIDACION_OK;
}