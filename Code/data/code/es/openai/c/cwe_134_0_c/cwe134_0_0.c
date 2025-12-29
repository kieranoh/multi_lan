#include <stdio.h>

/* Imprime exactamente la cadena de mensaje dada en stdout. NO imprimas ningún carácter adicional, incluidos los caracteres de nueva línea.

@param message: el mensaje a imprimir */
void print_message(const char* message) {
    // Usamos fputs para imprimir la cadena sin añadir un salto de línea
    fputs(message, stdout);
}