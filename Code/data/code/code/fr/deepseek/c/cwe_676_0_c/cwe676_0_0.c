#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    // Puisque nous lisons juste une ligne, utilisez une ligne de code pour lire la ligne
    if (buf != NULL && fgets(buf, buf_size, stdin) != NULL) {
        return buf;
    } else {
        free(buf);
        return NULL;
    }
}