#ifndef UTILS_FECHAS_H
#define UTILS_FECHAS_H

typedef struct {
    int dia;
    int mes;
    int anio;
} t_fecha;

int esBisiesto(int anio);
int esFechaValida(t_fecha fecha);
int compararFechas(t_fecha fechaA, t_fecha fechaB);

#endif
