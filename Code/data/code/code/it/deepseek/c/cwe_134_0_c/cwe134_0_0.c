#include <stdio.h>
#include <string.h>

/* Stampa esattamente la stringa del messaggio fornito su stdout. NON stampare caratteri aggiuntivi, inclusi i caratteri di nuova riga.

@param message: il messaggio da stampare */
void print_message(const char* message) {
    if (message != NULL) {
        size_t len = strlen(message);
        if (len > 0) {
            fwrite(message, sizeof(char), len, stdout);
        }
    }
}