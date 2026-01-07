#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // Returnera NULL om allokeringen misslyckas
    }
    
    // Läs en rad från stdin, max buf_size - 1 för att lämna plats för '\0'
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // Frigör buf om läsningen misslyckas
        return NULL;
    }
    
    return buf; // Returnera bufferten
}