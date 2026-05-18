#include <stdio.h>
#include "carga-miembros.h"
#include "../validaciones/validaciones-miembros.h"

void cargaMiembros(t_fecha fechaProceso){
    // Abro el arch, mientras tenga miembros por leer los parseo a Miembro y llamo a validarMiembro(miembro, fechaProceso) //

    // En caso de que la respuesta de validarMiembro sea OK guardo el mimebro en memoria, en caso contrario deberia de manejar los errores //

    // Tenemos que tener en cuenta que tenemos early return, entonces si alguna validacion falla ya vengo a este flujo y tnego
    // el codigo de error, por ende se que fallo (DNI o CUIT u otro) por lo tanto ya tengo info para hacer la auditoria
    // ya que ademas tengo el DNI de el miembro porque lo estoy parseando en este mismo flujo arriba 

    // Cierro el arch //
    // Logica de errores todavia no planeada al 100% //
}
