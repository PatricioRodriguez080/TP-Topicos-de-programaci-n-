#include <stdio.h>
#include <string.h>
#include "operaciones-miembros.h"
#include "../comparadores/comparadores.h"
#include "../../indice/indice.h"
#include "../../utils/utils-entrada.h"
#include "../validaciones/validaciones-miembros.h"

void altaMiembro(t_contexto_menu *ctx){
    (void) ctx;
}

void bajaMiembro(t_contexto_menu *ctx){
    long dni;
    Miembro clave;
    Miembro *vec;
    t_reg_indice regClave;
    int pos;

    if (!leerLong("DNI a dar de baja: ", &dni)){
        printf("Entrada invalida.\n");
        return;
    }
    memset(&clave, 0, sizeof(clave));
    clave.dni = dni;

    pos = indice_buscar(ctx->miembrosCompletos, &clave, ctx->miembrosCompletos->cantidad_elementos_actual, sizeof(Miembro), cmpMiembrosPorDni);
    if (pos == NO_EXISTE){
        printf("DNI inexistente.\n");
        return;
    }

    vec = (Miembro *) ctx->miembrosCompletos->vindice;
    if (vec[pos].estado == 'B'){
        printf("El miembro ya estaba dado de baja.\n");
        return;
    }
    vec[pos].estado = 'B';

    regClave.dni = dni;
    regClave.nro_reg = 0;
    indice_eliminar(ctx->exitoMiembros, &regClave, sizeof(t_reg_indice), cmpRegIndicePorDni);

    printf("Miembro %ld dado de baja.\n", dni);
}

void modificarMiembro(t_contexto_menu *ctx){
    long dni;
    Miembro clave, copia;
    Miembro *vec;
    int pos, opcion, res, xy;

    if (!leerLong("DNI a modificar: ", &dni)){
        printf("Entrada invalida.\n");
        return;
    }
    memset(&clave, 0, sizeof(clave));
    clave.dni = dni;
    pos = indice_buscar(ctx->miembrosCompletos, &clave, ctx->miembrosCompletos->cantidad_elementos_actual, sizeof(Miembro), cmpMiembrosPorDni);
    if (pos == NO_EXISTE){
        printf("DNI inexistente.\n");
        return;
    }

    vec = (Miembro *) ctx->miembrosCompletos->vindice;
    copia = vec[pos];

    printf("\n1) Apellido y Nombre\n");
    printf("2) Sexo\n");
    printf("3) Fecha de nacimiento\n");
    printf("4) Plan\n");
    printf("5) Email tutor\n");
    printf("6) Fecha ultima cuota\n");
    if (!leerInt("Opcion: ", &opcion)){
        printf("Cancelado.\n");
        return;
    }

    switch (opcion){
        case 1:
            if (!leerLineaTrim("Nuevo Apellido, Nombre: ", copia.apellidoNombre, sizeof(copia.apellidoNombre))) return;
            normalizarApellidoYNombre(copia.apellidoNombre);
            break;
        case 2:
            if (!leerChar("Nuevo sexo (F/M/O): ", &copia.sexo)) return;
            xy = (copia.sexo == 'F') ? 27 : (copia.sexo == 'M' ? 20 : 23);
            calcularCUIL(xy, copia.dni, copia.cuil);
            break;
        case 3:
            if (!leerFecha("Nueva fecha nacimiento (DD/MM/AAAA): ", &copia.fechaNacimiento)) return;
            calcularCategoria(copia.fechaNacimiento, ctx->fechaProceso, copia.categoria);
            break;
        case 4:
            if (!leerLineaTrim("Nuevo plan (BASIC/PREMIUM/VIP/FAMILY): ", copia.plan, sizeof(copia.plan))) return;
            break;
        case 5:
            if (!leerLineaTrim("Nuevo email tutor: ", copia.emailTutor, sizeof(copia.emailTutor))) return;
            break;
        case 6:
            if (!leerFecha("Nueva fecha ultima cuota (DD/MM/AAAA): ", &copia.fechaUltimaCuota)) return;
            break;
        default:
            printf("Opcion invalida.\n");
            return;
    }

    res = validarMiembro(copia, ctx->fechaProceso);
    if (res != VALIDACION_OK){
        printf("Validacion fallo (codigo %d). Cambios descartados.\n", res);
        return;
    }
    vec[pos] = copia;
    printf("Miembro actualizado.\n");
}

void mostrarInfoMiembro(t_contexto_menu *ctx){
    long dni;
    Miembro clave;
    Miembro *m;
    int pos;

    if (!leerLong("DNI a consultar: ", &dni)){
        printf("Entrada invalida.\n");
        return;
    }
    memset(&clave, 0, sizeof(clave));
    clave.dni = dni;
    pos = indice_buscar(ctx->miembrosCompletos, &clave, ctx->miembrosCompletos->cantidad_elementos_actual, sizeof(Miembro), cmpMiembrosPorDni);
    if (pos == NO_EXISTE){
        printf("DNI inexistente.\n");
        return;
    }

    m = &((Miembro *) ctx->miembrosCompletos->vindice)[pos];

    printf("\n--- MIEMBRO ---\n");
    printf("DNI            : %ld\n", m->dni);
    printf("CUIL           : %s\n",  m->cuil);
    printf("Apellido/Nombre: %s\n",  m->apellidoNombre);
    printf("Nacimiento     : %02d/%02d/%04d\n", m->fechaNacimiento.dia, m->fechaNacimiento.mes, m->fechaNacimiento.anio);
    printf("Sexo           : %c\n", m->sexo);
    printf("Afiliacion     : %02d/%02d/%04d\n", m->fechaAfiliacion.dia, m->fechaAfiliacion.mes, m->fechaAfiliacion.anio);
    printf("Categoria      : %s\n", m->categoria);
    printf("Ultima cuota   : %02d/%02d/%04d\n", m->fechaUltimaCuota.dia, m->fechaUltimaCuota.mes, m->fechaUltimaCuota.anio);
    printf("Estado         : %c\n", m->estado);
    printf("Plan           : %s\n", m->plan);
    printf("Email tutor    : %s\n", m->emailTutor);
}

void listarMiembrosPorDni(t_contexto_menu *ctx){
    Miembro *vec = (Miembro *) ctx->miembrosCompletos->vindice;
    unsigned i, n = ctx->miembrosCompletos->cantidad_elementos_actual;
    int mostrados = 0;

    printf("\n%-10s %-30s %-10s %-3s\n", "DNI", "APELLIDO Y NOMBRE", "PLAN", "EST");
    for (i = 0; i < n; i++){
        if (vec[i].estado == 'B') continue;
        printf("%-10ld %-30s %-10s %c\n", vec[i].dni, vec[i].apellidoNombre, vec[i].plan, vec[i].estado);
        mostrados++;
    }
    if (!mostrados) printf("(sin miembros activos)\n");
}

static void imprimirCelda(const t_reg_nombre *r, const char *plan){
    if (strcmp(r->plan, plan) == 0) printf("%-10ld ", r->dni);
    else                            printf("%-10d ", 0);
}

void listarMiembrosPorPlan(t_contexto_menu *ctx){
    Miembro *vec = (Miembro *) ctx->miembrosCompletos->vindice;
    unsigned n = ctx->miembrosCompletos->cantidad_elementos_actual;
    unsigned i;
    t_indice aux;
    t_reg_nombre tmp;
    t_reg_nombre *vecAux;

    indice_crear(&aux, n + 1, sizeof(t_reg_nombre));
    for (i = 0; i < n; i++){
        if (vec[i].estado == 'B') continue;
        strncpy(tmp.apellidoNombre, vec[i].apellidoNombre, sizeof(tmp.apellidoNombre));
        tmp.apellidoNombre[sizeof(tmp.apellidoNombre)-1] = '\0';
        tmp.dni = vec[i].dni;
        strncpy(tmp.plan, vec[i].plan, sizeof(tmp.plan));
        tmp.plan[sizeof(tmp.plan)-1] = '\0';
        indice_insertar(&aux, &tmp, sizeof(t_reg_nombre), cmpRegPorApellidoNombre);
    }

    printf("\n%-30s %-10s %-10s %-10s %-10s\n",
           "Plan / Indice", "BASIC", "PREMIUM", "VIP", "FAMILY");

    vecAux = (t_reg_nombre *) aux.vindice;
    for (i = 0; i < aux.cantidad_elementos_actual; i++){
        printf("%-30s ", vecAux[i].apellidoNombre);
        imprimirCelda(&vecAux[i], "BASIC");
        imprimirCelda(&vecAux[i], "PREMIUM");
        imprimirCelda(&vecAux[i], "VIP");
        imprimirCelda(&vecAux[i], "FAMILY");
        printf("\n");
    }

    indice_liberar(&aux);
}
