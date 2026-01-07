#include <stdio.h>

/* Imprimeix exactament la cadena de missatge donada a stdout. NO imprimeix cap caràcter addicional, incloent-hi caràcters de nova línia.

@param message: el missatge a imprimir */
void print_message(const char* message) {
    // Utilitzem fputs per imprimir el missatge sense afegir un caràcter de nova línia
    fputs(message, stdout);
}