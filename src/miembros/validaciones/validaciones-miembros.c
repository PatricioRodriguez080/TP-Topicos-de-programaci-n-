#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "validaciones-miembros.h"
#include "../../utils/utils-fechas.h"

int validarDNI(void *dato){
    DatosValidacionMiembro *d = (DatosValidacionMiembro *)dato;

    if (d->miembro->dni <= 1000000 ||
        d->miembro->dni >= 100000000){
        return ERROR_DNI;
    }
    return VALIDACION_OK;
}

int validarSexo(void *dato){
    DatosValidacionMiembro *d = (DatosValidacionMiembro *)dato;

    if (d->miembro->sexo != 'F' &&
        d->miembro->sexo != 'M' &&
        d->miembro->sexo != 'O'){
        return ERROR_SEXO;
    }
    return VALIDACION_OK;
}

int validarEstado(void *dato){
    DatosValidacionMiembro *d = (DatosValidacionMiembro *)dato;

    if (d->miembro->estado != 'A' &&
        d->miembro->estado != 'B'){
        return ERROR_ESTADO;
    }
    return VALIDACION_OK;
}

int validarPlan(void *dato){
    DatosValidacionMiembro *d = (DatosValidacionMiembro *)dato;

    if (strcmp(d->miembro->plan, "BASIC")   != 0 &&
        strcmp(d->miembro->plan, "PREMIUM") != 0 &&
        strcmp(d->miembro->plan, "VIP")     != 0 &&
        strcmp(d->miembro->plan, "FAMILY")  != 0){
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

int validarCUIL(void *dato){
    DatosValidacionMiembro *d = (DatosValidacionMiembro *)dato;
    char esperado[14];

    if (d->miembro->sexo == 'M'){
        calcularCUIL(20, d->miembro->dni, esperado);
        if (strcmp(d->miembro->cuil, esperado) == 0){
            return VALIDACION_OK;
        }
    } else if (d->miembro->sexo == 'F'){
        calcularCUIL(27, d->miembro->dni, esperado);
        if (strcmp(d->miembro->cuil, esperado) == 0){
            return VALIDACION_OK;
        }
    } else if (d->miembro->sexo == 'O'){
        calcularCUIL(20, d->miembro->dni, esperado);
        if (strcmp(d->miembro->cuil, esperado) == 0){
            return VALIDACION_OK;
        }
        calcularCUIL(27, d->miembro->dni, esperado);
        if (strcmp(d->miembro->cuil, esperado) == 0){
            return VALIDACION_OK;
        }
    }

    return ERROR_CUIL;
}

char *normalizarApellidoYNombre(char *cad){
    char *lect = cad, *esc = cad;
    int primeraLetraPalabra;
    int posicionPalabra = 0;

    while (*lect){
        while (*lect && (isspace(*lect) || *lect == ','))
            lect++;

        if (*lect){
            posicionPalabra++;

            if (posicionPalabra == 2){
                *esc = ',';
                esc++;
                *esc = ' ';
                esc++;
            } else if (posicionPalabra > 2){
                *esc = ' ';
                esc++;
            }

            primeraLetraPalabra = 1;
            while (*lect && !isspace(*lect) && *lect != ','){
                *esc = primeraLetraPalabra ? toupper(*lect) : tolower(*lect);
                primeraLetraPalabra = 0;
                esc++;
                lect++;
            }
        }
    }

    *esc = '\0';
    return cad;
}

int validarApellidoYNombre(void *dato){
    DatosValidacionMiembro *d = (DatosValidacionMiembro *)dato;
    char esperado[60];

    strcpy(esperado, d->miembro->apellidoNombre);
    normalizarApellidoYNombre(esperado);

    if (strcmp(d->miembro->apellidoNombre, esperado) != 0){
        return ERROR_APELLIDO_NOMBRE;
    }
    return VALIDACION_OK;
}

int validarFechaNacimiento(void *dato){
    DatosValidacionMiembro *d = (DatosValidacionMiembro *)dato;

    if (!esFechaValida(d->miembro->fechaNacimiento)){
        return ERROR_FECHA_NACIMIENTO;
    }
    if (calcularEdad(d->miembro->fechaNacimiento, d->fechaProceso) < 10){
        return ERROR_FECHA_NACIMIENTO;
    }
    return VALIDACION_OK;
}

int validarFechaAfiliacion(void *dato){
    DatosValidacionMiembro *d = (DatosValidacionMiembro *)dato;

    if (!esFechaValida(d->miembro->fechaAfiliacion)){
        return ERROR_FECHA_AFILIACION;
    }
    if (compararFechas(d->miembro->fechaAfiliacion, d->miembro->fechaNacimiento) < 0){
        return ERROR_FECHA_AFILIACION;
    }
    if (compararFechas(d->miembro->fechaAfiliacion, d->fechaProceso) > 0){
        return ERROR_FECHA_AFILIACION;
    }
    return VALIDACION_OK;
}

int validarFechaUltimaCuota(void *dato){
    DatosValidacionMiembro *d = (DatosValidacionMiembro *)dato;

    if (!esFechaValida(d->miembro->fechaUltimaCuota)){
        return ERROR_FECHA_ULTIMA_CUOTA;
    }
    if (compararFechas(d->miembro->fechaUltimaCuota, d->miembro->fechaAfiliacion) < 0){
        return ERROR_FECHA_ULTIMA_CUOTA;
    }
    if (compararFechas(d->miembro->fechaUltimaCuota, d->fechaProceso) > 0){
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

int validarCategoria(void *dato){
    DatosValidacionMiembro *d = (DatosValidacionMiembro *)dato;
    char esperada[10];

    calcularCategoria(d->miembro->fechaNacimiento, d->fechaProceso, esperada);
    if (strcmp(d->miembro->categoria, esperada) != 0){
        return ERROR_CATEGORIA;
    }
    return VALIDACION_OK;
}

int esEmailValido(const char *email){
    int i;
    int posArroba = -1;
    int tienePuntoEnDominio = 0;

    for (i = 0; email[i] != '\0'; i++){
        char c = email[i];

        if (c == '@'){
            if (posArroba != -1) return 0;
            posArroba = i;
        } else if (c == '.'){
            if (posArroba != -1){
                tienePuntoEnDominio = 1;
            }
        } else if (!isalnum(c)){
            return 0;
        }
    }

    if (posArroba <= 0) return 0;
    if (email[posArroba + 1] == '\0') return 0;
    if (!tienePuntoEnDominio) return 0;

    return 1;
}

int validarEmailTutor(void *dato){
    DatosValidacionMiembro *d = (DatosValidacionMiembro *)dato;

    if (strcmp(d->miembro->categoria, "MENOR") == 0 && d->miembro->emailTutor[0] == '\0'){
        return ERROR_EMAIL_TUTOR;
    }
    if (d->miembro->emailTutor[0] != '\0' && !esEmailValido(d->miembro->emailTutor)){
        return ERROR_EMAIL_TUTOR;
    }
    return VALIDACION_OK;
}

int validarMiembro(Miembro miembro, t_fecha fechaProceso){
    DatosValidacionMiembro datos;

    datos.miembro = &miembro;
    datos.fechaProceso = fechaProceso;

    ValidadorFn validaciones[] = {
        validarDNI,
        validarCUIL,
        validarApellidoYNombre,
        validarFechaNacimiento,
        validarSexo,
        validarFechaAfiliacion,
        validarCategoria,
        validarFechaUltimaCuota,
        validarEstado,
        validarPlan,
        validarEmailTutor
    };

    int cantidad = sizeof(validaciones) / sizeof(validaciones[0]);
    int i, res;

    for (i = 0; i < cantidad; i++){
        res = ejecutarValidacion(&datos, validaciones[i]);
        if (res != VALIDACION_OK) return res;
    }

    return VALIDACION_OK;
}