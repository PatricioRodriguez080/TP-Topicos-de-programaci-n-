#include <stdio.h>
#include "archivos.h"

void armarNombreArchivo(char *out, size_t n, const char *base, t_fecha f, const char *ext){
    snprintf(out, n, "%s_%04d%02d%02d.%s", base, f.anio, f.mes, f.dia, ext);
}

int existeArchivo(const char *path){
    FILE *fp = fopen(path, "rb");
    if (!fp) return 0;
    fclose(fp);
    return 1;
}
