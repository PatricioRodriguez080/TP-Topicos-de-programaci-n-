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
int calcularEdad(t_fecha fechaNacimiento, t_fecha fechaProceso);
int parsearFecha(const char *str, t_fecha *fecha);
t_fecha pedirFechaProceso(void);

#endif
