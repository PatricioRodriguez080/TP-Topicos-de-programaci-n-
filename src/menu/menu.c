#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "menu.h"
#include "../operaciones/operaciones-miembros.h"
#include "../operaciones/operaciones-titulos.h"

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
            case 'a': op_altaMiembro(ctx);           break;
            case 'b': op_altaTitulo(ctx);            break;
            case 'c': op_bajaMiembro(ctx);           break;
            case 'd': op_bajaTitulo(ctx);            break;
            case 'e': op_modificarMiembro(ctx);      break;
            case 'f': op_modificarTitulo(ctx);       break;
            case 'g': op_mostrarInfoMiembro(ctx);    break;
            case 'h': op_alquilarTitulo(ctx);        break;
            case 'i': op_listarMiembrosPorDni(ctx);  break;
            case 'j': op_listarMiembrosPorPlan(ctx); break;
            case 'k': salir = true;                  break;
            default:  printf("Opcion invalida.\n"); break;
        }
    }

    printf("Saliendo del programa...\n");
}
