#include <stdio.h>
#include <string.h>
#include "operaciones-titulos.h"
#include "../../alquileres/alquileres.h"
#include "../comparadores/comparadores.h"
#include "../../miembros/comparadores/comparadores.h"
#include "../../indice/indice.h"
#include "../../utils/utils-entrada.h"
#include "../../miembros/validaciones/validaciones-miembros.h"
#include "../validaciones/validaciones-titulos.h"

void altaTitulo(t_contexto_menu *ctx){
    Titulo nuevo, clave;
    t_reg_indice_titulo reg;
    t_reg_indice_titulo *exitos;
    int pos, res;
    unsigned i;

    memset(&nuevo, 0, sizeof(nuevo));

    if (!leerInt("ID de pelicula: ", &nuevo.idPelicula)){
        printf("Entrada invalida.\n");
        return;
    }
    memset(&clave, 0, sizeof(clave));
    clave.idPelicula = nuevo.idPelicula;
    if (indice_buscar(ctx->titulosCompletos, &clave, ctx->titulosCompletos->cantidad_elementos_actual, sizeof(Titulo), cmpTitulosPorId) != NO_EXISTE){
        printf("Ya existe un titulo con ese ID.\n");
        return;
    }

    if (!leerLineaTrim("Titulo: ", nuevo.titulo, sizeof(nuevo.titulo))) return;
    normalizarApellidoYNombre(nuevo.titulo);
    if (!leerLineaTrim("Genero (Accion/Drama/Comedia/Terror): ", nuevo.genero, sizeof(nuevo.genero))) return;
    if (!leerInt("Stock: ", &nuevo.stock)) return;
    nuevo.estado = 'A';

    res = validarTitulo(nuevo);
    if (res != VALIDACION_OK){
        printf("Validacion fallo (codigo %d). Alta cancelada.\n", res);
        return;
    }

    indice_insertar(ctx->titulosCompletos, &nuevo, sizeof(Titulo), cmpTitulosPorId);

    pos = indice_buscar(ctx->titulosCompletos, &nuevo, ctx->titulosCompletos->cantidad_elementos_actual, sizeof(Titulo), cmpTitulosPorId);

    // Esto podemos ver si tenemos alguna otra forma de hacerlo para ver si es mas optimo, no se me ocurre otra cosa de momento //
    exitos = (t_reg_indice_titulo *) ctx->exitoTitulos->vindice;
    for (i = 0; i < ctx->exitoTitulos->cantidad_elementos_actual; i++){
        if ((int) exitos[i].nro_reg >= pos) exitos[i].nro_reg++;
    }

    reg.idPelicula = nuevo.idPelicula;
    reg.nro_reg = (unsigned) pos;
    indice_insertar(ctx->exitoTitulos, &reg, sizeof(t_reg_indice_titulo), cmpRegIndiceTituloPorId);

    printf("Titulo %d dado de alta.\n", nuevo.idPelicula);
}

void bajaTitulo(t_contexto_menu *ctx){
    int id;
    Titulo clave;
    Titulo *vec;
    t_reg_indice_titulo regClave;
    int pos;

    if (!leerInt("ID de pelicula a dar de baja: ", &id)){
        printf("Entrada invalida.\n");
        return;
    }
    memset(&clave, 0, sizeof(clave));
    clave.idPelicula = id;

    pos = indice_buscar(ctx->titulosCompletos, &clave,
                        ctx->titulosCompletos->cantidad_elementos_actual,
                        sizeof(Titulo), cmpTitulosPorId);
    if (pos == NO_EXISTE){
        printf("Titulo inexistente.\n");
        return;
    }

    vec = (Titulo *) ctx->titulosCompletos->vindice;
    if (vec[pos].estado == 'B'){
        printf("El titulo ya estaba dado de baja.\n");
        return;
    }
    vec[pos].estado = 'B';

    regClave.idPelicula = id;
    regClave.nro_reg = 0;
    indice_eliminar(ctx->exitoTitulos, &regClave,
                    sizeof(t_reg_indice_titulo), cmpRegIndiceTituloPorId);

    printf("Titulo %d dado de baja.\n", id);
}

void modificarTitulo(t_contexto_menu *ctx){
    int id, opcion, res;
    Titulo clave, copia;
    Titulo *vec;
    int pos;

    if (!leerInt("ID de pelicula a modificar: ", &id)){
        printf("Entrada invalida.\n");
        return;
    }
    memset(&clave, 0, sizeof(clave));
    clave.idPelicula = id;
    pos = indice_buscar(ctx->titulosCompletos, &clave,
                        ctx->titulosCompletos->cantidad_elementos_actual,
                        sizeof(Titulo), cmpTitulosPorId);
    if (pos == NO_EXISTE){
        printf("Titulo inexistente.\n");
        return;
    }

    vec = (Titulo *) ctx->titulosCompletos->vindice;
    copia = vec[pos];

    printf("\n1) Titulo\n2) Genero\n3) Stock\n");
    if (!leerInt("Opcion: ", &opcion)) return;

    switch (opcion){
        case 1:
            if (!leerLineaTrim("Nuevo titulo: ",
                               copia.titulo, sizeof(copia.titulo))) return;
            normalizarApellidoYNombre(copia.titulo);
            break;
        case 2:
            if (!leerLineaTrim("Nuevo genero (Accion/Drama/Comedia/Terror): ",
                               copia.genero, sizeof(copia.genero))) return;
            break;
        case 3:
            if (!leerInt("Nuevo stock: ", &copia.stock)) return;
            break;
        default:
            printf("Opcion invalida.\n");
            return;
    }

    res = validarTitulo(copia);
    if (res != VALIDACION_OK){
        printf("Validacion fallo (codigo %d). Cambios descartados.\n", res);
        return;
    }
    vec[pos] = copia;
    printf("Titulo actualizado.\n");
}

void alquilarTitulo(t_contexto_menu *ctx){
    long dni;
    int id, posM, posT;
    Miembro claveM;
    Titulo  claveT;
    Miembro *vecM;
    Titulo  *vecT;

    if (!leerLong("DNI del miembro: ", &dni)){
        printf("Entrada invalida.\n");
        return;
    }
    memset(&claveM, 0, sizeof(claveM));
    claveM.dni = dni;
    posM = indice_buscar(ctx->miembrosCompletos, &claveM,
                         ctx->miembrosCompletos->cantidad_elementos_actual,
                         sizeof(Miembro), cmpMiembrosPorDni);
    if (posM == NO_EXISTE){
        printf("DNI inexistente.\n");
        return;
    }

    vecM = (Miembro *) ctx->miembrosCompletos->vindice;
    if (vecM[posM].estado != 'A'){
        printf("El miembro esta dado de baja.\n");
        return;
    }

    if (!leerInt("ID de pelicula: ", &id)){
        printf("Entrada invalida.\n");
        return;
    }
    memset(&claveT, 0, sizeof(claveT));
    claveT.idPelicula = id;
    posT = indice_buscar(ctx->titulosCompletos, &claveT,
                         ctx->titulosCompletos->cantidad_elementos_actual,
                         sizeof(Titulo), cmpTitulosPorId);
    if (posT == NO_EXISTE){
        printf("Titulo inexistente.\n");
        return;
    }

    vecT = (Titulo *) ctx->titulosCompletos->vindice;
    if (vecT[posT].estado != 'A'){
        printf("El titulo esta dado de baja.\n");
        return;
    }
    if (vecT[posT].stock <= 0){
        printf("Sin stock disponible.\n");
        return;
    }

    if (strcmp(vecM[posM].plan, "BASIC") == 0){
        if (contarAlquileresActivosDeMiembro(ctx->alquileres, dni) >= 2){
            printf("Plan BASIC: maximo 2 alquileres simultaneos.\n");
            return;
        }
    }

    vecT[posT].stock--;
    if (!registrarAlquiler(ctx->alquileres, dni, id, ctx->fechaProceso)){
        printf("No se pudo registrar el alquiler.\n");
        vecT[posT].stock++;
        return;
    }
    printf("Alquiler registrado.\n");
}
