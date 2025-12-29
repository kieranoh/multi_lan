#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // Gestione dell'errore di allocazione
    }
    
    // Legge una riga da stdin nel buffer, assicurandosi di non superare buf_size - 1
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // Libera il buffer in caso di errore nella lettura
        return NULL;
    }
    
    return buf; // Restituisce il buffer contenente la riga letta
}