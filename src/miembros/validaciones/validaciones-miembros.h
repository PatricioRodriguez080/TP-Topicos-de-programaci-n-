#ifndef VALIDACIONES_MIEMBROS_H
#define VALIDACIONES_MIEMBROS_H

#include "../../utils/utils-fechas.h"
#include "../../utils/utils-validaciones.h"
#include "../miembro.h"

#define ERROR_DNI               1
#define ERROR_SEXO              2
#define ERROR_ESTADO            3
#define ERROR_PLAN              4
#define ERROR_CUIL              5
#define ERROR_FECHA_NACIMIENTO  6
#define ERROR_FECHA_AFILIACION  7
#define ERROR_CATEGORIA            8
#define ERROR_EMAIL_TUTOR          9
#define ERROR_FECHA_ULTIMA_CUOTA   10
#define ERROR_APELLIDO_NOMBRE      11

typedef struct {
    Miembro *miembro;
    t_fecha fechaProceso;
} DatosValidacionMiembro;

int  validarDNI(void *dato);
int  validarSexo(void *dato);
int  validarEstado(void *dato);
int  validarPlan(void *dato);
int  validarCUIL(void *dato);
int  validarApellidoYNombre(void *dato);
int  validarFechaNacimiento(void *dato);
int  validarFechaAfiliacion(void *dato);
int  validarFechaUltimaCuota(void *dato);
int  validarCategoria(void *dato);
int  validarEmailTutor(void *dato);

void calcularCUIL(int xyInicial, long dni, char salida[14]);
char *normalizarApellidoYNombre(char *cad);
void calcularCategoria(t_fecha fechaNacimiento, t_fecha fechaProceso, char salida[10]);
int  esEmailValido(const char *email);

int  validarMiembro(Miembro miembro, t_fecha fechaProceso);

#endif
