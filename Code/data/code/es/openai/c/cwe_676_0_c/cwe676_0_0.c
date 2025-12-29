#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // Manejo de error en la asignación de memoria
    }
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // Libera el búfer en caso de error
        return NULL;
    }
    return buf;
}