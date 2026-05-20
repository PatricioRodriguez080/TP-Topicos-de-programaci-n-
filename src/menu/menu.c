#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "menu.h"

// Estas funciones creo que quedarian mejor si las ponemos dentro del modulo al que pertenecen, las importamos aca y las llamamos //
void altaMiembro(t_contexto_menu *ctx){
    // contenido, leer comentario de arriba tambien //
}

void altaTitulo(t_contexto_menu *ctx){
    // contenido, leer comentario de arriba tambien //
}

void bajaMiembro(t_contexto_menu *ctx){
    // contenido, leer comentario de arriba tambien //
}

void bajaTitulo(t_contexto_menu *ctx){
    // contenido, leer comentario de arriba tambien //
}

void modificarMiembro(t_contexto_menu *ctx){
    // contenido, leer comentario de arriba tambien //
}

void modificarTitulo(t_contexto_menu *ctx){
    // contenido, leer comentario de arriba tambien //
}

void mostrarInfoMiembro(t_contexto_menu *ctx){
    // contenido, leer comentario de arriba tambien //
}

void alquilarTitulo(t_contexto_menu *ctx){
    // contenido, leer comentario de arriba tambien //
}

static void listarMiembrosPorDni(t_contexto_menu *ctx){
    // contenido, leer comentario de arriba tambien //
}

void listarMiembrosPorPlan(t_contexto_menu *ctx){
    // contenido, leer comentario de arriba tambien //
}

void imprimirOpciones(void){
    printf("\n=== MENU DE OPERACIONES ===\n");
    printf("  a. Alta de miembro\n");
    printf("  b. Alta de un titulo\n");
    printf("  c. Baja de un miembro\n");
    printf("  d. Baja de un titulo\n");
    printf("  e. Modificacion de un miembro\n");
    printf("  f. Modificacion de un titulo\n");
    printf("  g. Mostrar informacion de un miembro\n");
    printf("  h. Alquiler de un titulo\n");
    printf("  i. Listado de miembros ordenados por DNI\n");
    printf("  j. Listado miembros por Plan\n");
    printf("  k. Salir\n");
    printf("Opcion: ");
}

char leerOpcion(void){
    char buffer[16];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL){
        return 'k';
    }
    return buffer[0];
}

void mostrarMenu(t_contexto_menu *ctx){
    bool salir = false;
    char opcion;

    while (!salir){
        imprimirOpciones();
        opcion = leerOpcion();

        switch (opcion){
            case 'a': altaMiembro(ctx); break;
            case 'b': altaTitulo(ctx); break;
            case 'c': bajaMiembro(ctx); break;
            case 'd': bajaTitulo(ctx); break;
            case 'e': modificarMiembro(ctx); break;
            case 'f': modificarTitulo(ctx); break;
            case 'g': mostrarInfoMiembro(ctx); break;
            case 'h': alquilarTitulo(ctx); break;
            case 'i': listarMiembrosPorDni(ctx); break;
            case 'j': listarMiembrosPorPlan(ctx); break;
            case 'k': salir = true; break;
            default:  printf("Opcion invalida.\n"); break;
        }
    }

    printf("Saliendo del programa...\n");
}
