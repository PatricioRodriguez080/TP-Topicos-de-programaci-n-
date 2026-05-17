#include <stdio.h>
#include <string.h>
#include "validaciones-miembros.h"
#include "utils-fechas.h"

int validarDNI(long dni){
    if (dni <= 1000000 || dni >= 100000000){
        return ERROR_DNI;
    }
    return VALIDACION_OK;
}

int validarSexo(char sexo){
    if (sexo != 'F' && sexo != 'M' && sexo != 'O'){
        return ERROR_SEXO;
    }
    return VALIDACION_OK;
}

int validarEstado(char estado){
    if (estado != 'A' && estado != 'B'){
        return ERROR_ESTADO;
    }
    return VALIDACION_OK;
}

int validarPlan(const char *plan){
    if (strcmp(plan, "BASIC")   != 0 &&
        strcmp(plan, "PREMIUM") != 0 &&
        strcmp(plan, "VIP")     != 0 &&
        strcmp(plan, "FAMILY")  != 0){
            return ERROR_PLAN;
        }
    return VALIDACION_OK;
}

void calcularCUIL(int xyInicial, long dni, char salida[14]){
    int pesos[10] = {5, 4, 3, 2, 7, 6, 5, 4, 3, 2};
    int digitos[10];
    long dniRestante = dni;
    int i;
    int suma = 0;
    int resto;
    int xyFinal = xyInicial;
    int z;

    digitos[0] = xyInicial / 10;
    digitos[1] = xyInicial % 10;
    for (i = 9; i >= 2; i--){
        digitos[i] = dniRestante % 10;
        dniRestante /= 10;
    }

    for (i = 0; i < 10; i++){
        suma += digitos[i] * pesos[i];
    }

    resto = suma % 11;

    if (resto == 0){
        z = 0;
    } else if (resto == 1){
        if (xyInicial == 20){
            z = 9;
            xyFinal = 23;
        } else if (xyInicial == 27){
            z = 4;
            xyFinal = 23;
        } else {
            z = 11 - resto;
        }
    } else {
        z = 11 - resto;
    }

    // sprintf(destino, "formato", valores) //
    // Armo el string y lo guardo en salida //
    // Borrar este comentario despues, por el momento es de ayuda :) //
    sprintf(salida, "%02d-%08ld-%d", xyFinal, dni, z);
}

int validarCUIL(const char *cuil, long dni, char sexo){
    char esperado[14];

    if (sexo == 'M'){
        calcularCUIL(20, dni, esperado);
        if (strcmp(cuil, esperado) == 0){
            return VALIDACION_OK;
        }
    } else if (sexo == 'F'){
        calcularCUIL(27, dni, esperado);
        if (strcmp(cuil, esperado) == 0){
            return VALIDACION_OK;
        }
    } else if (sexo == 'O'){
        calcularCUIL(20, dni, esperado);
        if (strcmp(cuil, esperado) == 0){
            return VALIDACION_OK;
        }
        calcularCUIL(27, dni, esperado);
        if (strcmp(cuil, esperado) == 0){
            return VALIDACION_OK;
        }
    }

    return ERROR_CUIL;
}

int validarFechaNacimiento(t_fecha fechaNacimiento, t_fecha fechaProceso){
    if (!esFechaValida(fechaNacimiento)){
        return ERROR_FECHA_NACIMIENTO;
    }
    if (calcularEdad(fechaNacimiento, fechaProceso) < 10){
        return ERROR_FECHA_NACIMIENTO;
    }
    return VALIDACION_OK;
}

int validarFechaAfiliacion(t_fecha fechaAfiliacion,t_fecha fechaNacimiento,t_fecha fechaProceso){
    if (!esFechaValida(fechaAfiliacion)){
        return ERROR_FECHA_AFILIACION;
    }
    if (compararFechas(fechaAfiliacion, fechaNacimiento) < 0){
        return ERROR_FECHA_AFILIACION;
    }
    if (compararFechas(fechaAfiliacion, fechaProceso) > 0){
        return ERROR_FECHA_AFILIACION;
    }
    return VALIDACION_OK;
}

int validarFechaUltimaCuota(t_fecha fechaUltimaCuota, t_fecha fechaAfiliacion, t_fecha fechaProceso){
    if (!esFechaValida(fechaUltimaCuota)){
        return ERROR_FECHA_ULTIMA_CUOTA;
    }
    if (compararFechas(fechaUltimaCuota, fechaAfiliacion) < 0){
        return ERROR_FECHA_ULTIMA_CUOTA;
    }
    if (compararFechas(fechaUltimaCuota, fechaProceso) > 0){
        return ERROR_FECHA_ULTIMA_CUOTA;
    }
    return VALIDACION_OK;
}

void calcularCategoria(t_fecha fechaNacimiento, t_fecha fechaProceso, char salida[10]){
    int edad = calcularEdad(fechaNacimiento, fechaProceso);
    if (edad < 18){
        strcpy(salida, "MENOR");
    } else {
        strcpy(salida, "ADULTO");
    }
}

int validarCategoria(const char *categoria, t_fecha fechaNacimiento, t_fecha fechaProceso){
    char esperada[10];
    calcularCategoria(fechaNacimiento, fechaProceso, esperada);
    if (strcmp(categoria, esperada) != 0){
        return ERROR_CATEGORIA;
    }
    return VALIDACION_OK;
}

int validarEmailTutor(const char *emailTutor, const char *categoria){
    // aca tengo que agregar la validacion de emails que esta explicada en el TP //
    if (strcmp(categoria, "MENOR") == 0 && emailTutor[0] == '\0'){
        return ERROR_EMAIL_TUTOR;
    }
    return VALIDACION_OK;
}

int validarMiembro(Miembro miembro, t_fecha fechaProceso){
    int res;

    res = validarDNI(miembro.dni);
    if (res != VALIDACION_OK) return res;

    res = validarCUIL(miembro.cuil, miembro.dni, miembro.sexo);
    if (res != VALIDACION_OK) return res;

    res = validarFechaNacimiento(miembro.fechaNacimiento, fechaProceso);
    if (res != VALIDACION_OK) return res;

    res = validarSexo(miembro.sexo);
    if (res != VALIDACION_OK) return res;

    res = validarFechaAfiliacion(miembro.fechaAfiliacion, miembro.fechaNacimiento, fechaProceso);
    if (res != VALIDACION_OK) return res;

    res = validarCategoria(miembro.categoria, miembro.fechaNacimiento, fechaProceso);
    if (res != VALIDACION_OK) return res;

    res = validarFechaUltimaCuota(miembro.fechaUltimaCuota, miembro.fechaAfiliacion, fechaProceso);
    if (res != VALIDACION_OK) return res;

    res = validarEstado(miembro.estado);
    if (res != VALIDACION_OK) return res;

    res = validarPlan(miembro.plan);
    if (res != VALIDACION_OK) return res;

    res = validarEmailTutor(miembro.emailTutor, miembro.categoria);
    if (res != VALIDACION_OK) return res;

    return VALIDACION_OK;
}