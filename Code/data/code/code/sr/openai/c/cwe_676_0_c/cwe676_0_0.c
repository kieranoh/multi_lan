#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // Vraćamo NULL ako alokacija zakaže
    }
    
    // Čitamo jedan red iz stdin
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // Oslobađamo memoriju ako čitanje ne uspe
        return NULL;
    }

    return buf;
}