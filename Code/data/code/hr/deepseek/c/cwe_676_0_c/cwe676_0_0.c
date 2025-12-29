#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL;
    }
    
    // Čitamo samo jedan redak, ali ograničavamo na buf_size-1 znakova
    // kako bismo ostavili prostor za null terminator
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf);
        return NULL;
    }
    
    return buf;
}