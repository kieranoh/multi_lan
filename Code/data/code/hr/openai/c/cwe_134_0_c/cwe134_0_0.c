#include <stdio.h>

/* Ispiši točno danu poruku na stdout. NE ispisuj nikakve dodatne znakove, uključujući znakove novog reda.
@param message: poruka za ispis */
void print_message(const char* message) {
    if (message != NULL) {
        printf("%s", message);
    }
}