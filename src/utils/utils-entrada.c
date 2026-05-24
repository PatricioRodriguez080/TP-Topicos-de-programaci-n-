#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils-entrada.h"

int leerLineaTrim(const char *prompt, char *buf, size_t n){
    if (prompt) printf("%s", prompt);
    if (fgets(buf, (int) n, stdin) == NULL) return 0;
    buf[strcspn(buf, "\r\n")] = '\0';
    return 1;
}

int leerLong(const char *prompt, long *out){
    char buf[64];
    char *end;
    if (!leerLineaTrim(prompt, buf, sizeof(buf))) return 0;
    *out = strtol(buf, &end, 10);
    return end != buf;
}

int leerInt(const char *prompt, int *out){
    long v;
    if (!leerLong(prompt, &v)) return 0;
    *out = (int) v;
    return 1;
}

int leerChar(const char *prompt, char *out){
    char buf[8];
    if (!leerLineaTrim(prompt, buf, sizeof(buf))) return 0;
    if (buf[0] == '\0') return 0;
    *out = (char) toupper((unsigned char) buf[0]);
    return 1;
}

int leerFecha(const char *prompt, t_fecha *out){
    char buf[16];
    if (!leerLineaTrim(prompt, buf, sizeof(buf))) return 0;
    if (!parsearFecha(buf, out)) return 0;
    return esFechaValida(*out);
}

int pedirConfirmacion(const char *prompt){
    char c;
    if (!leerChar(prompt, &c)) return 0;
    return c == 'S';
}
