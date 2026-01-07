#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // Vraćamo NULL ukoliko alokacija ne uspe
    }
    
    // Čitamo samo jedan redak iz stdin
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // Osiguravamo da oslobodimo memoriju ukoliko dođe do greške
        return NULL;
    }
    
    return buf; // Vraćamo bafer koji sadrži redak pročitan iz stdin
}