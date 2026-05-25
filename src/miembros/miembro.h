#ifndef MIEMBRO_H
#define MIEMBRO_H

#include "../utils/utils-fechas.h"

typedef struct {
    long    dni;
    char    cuil[14];
    char    apellidoNombre[60];
    t_fecha fechaNacimiento;
    char    sexo;
    t_fecha fechaAfiliacion;
    char    categoria[10];
    t_fecha fechaUltimaCuota;
    char    estado;
    char    plan[10];
    char    emailTutor[30];
} Miembro;

#endif
