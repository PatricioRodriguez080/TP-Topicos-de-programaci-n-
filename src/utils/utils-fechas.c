#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "utils-fechas.h"

int esBisiesto(int anio){
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)){
        return 1;
    }
    return 0;
}

int esFechaValida(t_fecha fecha){
    int diasMes;

    if (fecha.mes < 1 || fecha.mes > 12){
        return 0;
    }
    if (fecha.dia < 1){
        return 0;
    }

    switch (fecha.mes){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            diasMes = 31;
            break;
        case 4: case 6: case 9: case 11:
            diasMes = 30;
            break;
        case 2:
            if (esBisiesto(fecha.anio)){
                diasMes = 29;
            } else {
                diasMes = 28;
            }
            break;
        default:
            diasMes = 0;
            break;
    }

    if (fecha.dia > diasMes){
        return 0;
    }
    return 1;
}

int compararFechas(t_fecha fechaA, t_fecha fechaB){
    if (fechaA.anio < fechaB.anio) return -1;
    if (fechaA.anio > fechaB.anio) return 1;
    if (fechaA.mes  < fechaB.mes)  return -1;
    if (fechaA.mes  > fechaB.mes)  return 1;
    if (fechaA.dia  < fechaB.dia)  return -1;
    if (fechaA.dia  > fechaB.dia)  return 1;
    return 0;
}

int calcularEdad(t_fecha fechaNacimiento, t_fecha fechaProceso){
    int edad = fechaProceso.anio - fechaNacimiento.anio;
    if (fechaProceso.mes < fechaNacimiento.mes ||
        (fechaProceso.mes == fechaNacimiento.mes && fechaProceso.dia < fechaNacimiento.dia)){
        edad--;
    }
    return edad;
}

int parsearFecha(const char *str, t_fecha *fecha){
    return sscanf(str, "%d/%d/%d", &fecha->dia, &fecha->mes, &fecha->anio) == 3;
}

t_fecha pedirFechaProceso(void){
    char buffer[32];
    t_fecha fecha;
    time_t ahora;
    bool fechaLista = false;
    bool usarSistema = false;

    while (!fechaLista && !usarSistema){
        printf("Ingrese fecha de proceso (DD/MM/AAAA) o ENTER para usar fecha del sistema: ");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL){
            usarSistema = true;
        } else {
            buffer[strcspn(buffer, "\r\n")] = '\0';

            if (buffer[0] == '\0'){
                usarSistema = true;
            } else if (parsearFecha(buffer, &fecha) && esFechaValida(fecha)){
                fechaLista = true;
            } else {
                printf("Fecha invalida.\n");
            }
        }
    }

    if (usarSistema){
        char fechaStr[16];
        ahora = time(NULL);
        strftime(fechaStr, sizeof(fechaStr), "%d/%m/%Y", localtime(&ahora));
        parsearFecha(fechaStr, &fecha);
    }

    return fecha;
}
