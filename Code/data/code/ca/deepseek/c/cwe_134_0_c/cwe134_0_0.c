#include <stdio.h>

/* Imprimeix exactament la cadena de missatge donada a stdout. NO imprimeix cap caràcter addicional, incloent-hi caràcters de nova línia.

@param message: el missatge a imprimir */
void print_message(const char* message) {
    if (message != NULL) {
        printf("%s", message);
    }
}