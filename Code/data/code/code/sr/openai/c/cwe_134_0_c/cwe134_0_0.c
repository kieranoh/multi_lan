#include <stdio.h>

/* Ispisuje tačno dati string poruke na stdout. NE ispisujte dodatne karaktere, uključujući karaktere novog reda.

@param message: poruka za ispis */
void print_message(const char* message) {
    // Ispisuje poruku na stdout bez dodatnih karaktera
    printf("%s", message);
}