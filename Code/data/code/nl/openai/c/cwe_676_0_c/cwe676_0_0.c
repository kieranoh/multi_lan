#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // Controleer op succesvolle allocatie
    }
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // Vrijgeven bij fout
        return NULL;
    }
    return buf;
}