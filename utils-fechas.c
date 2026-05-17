#include "utils-fechas.h"

int esBisiesto(int anio)
{
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)){
        return 1;
    }
    return 0;
}

int esFechaValida(t_fecha fecha)
{
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

int compararFechas(t_fecha fechaA, t_fecha fechaB)
{
    if (fechaA.anio < fechaB.anio) return -1;
    if (fechaA.anio > fechaB.anio) return 1;
    if (fechaA.mes  < fechaB.mes)  return -1;
    if (fechaA.mes  > fechaB.mes)  return 1;
    if (fechaA.dia  < fechaB.dia)  return -1;
    if (fechaA.dia  > fechaB.dia)  return 1;
    return 0;
}
