#ifndef VALIDACIONES_MIEMBROS_H
#define VALIDACIONES_MIEMBROS_H

#define VALIDACION_OK   0
#define ERROR_DNI       1
#define ERROR_SEXO      2
#define ERROR_ESTADO    3
#define ERROR_PLAN      4

typedef struct {
    int dia;
    int mes;
    int anio;
} t_fecha;

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

int  validarDNI(long dni);
int  validarSexo(char sexo);
int  validarEstado(char estado);
int  validarPlan(const char *plan);

#endif
