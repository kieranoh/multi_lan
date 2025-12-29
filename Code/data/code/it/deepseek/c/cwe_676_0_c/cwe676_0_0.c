#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    // Poiché stiamo leggendo solo una riga, usa una riga di codice per leggere la riga
    if (buf != NULL && fgets(buf, buf_size, stdin) != NULL) {
        // Rimuove il carattere newline finale se presente
        for (int i = 0; i < buf_size; i++) {
            if (buf[i] == '\n') {
                buf[i] = '\0';
                break;
            }
        }
    } else {
        // In caso di errore di allocazione o lettura, libera la memoria e restituisce NULL
        free(buf);
        buf = NULL;
    }
    return buf;
}