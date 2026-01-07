#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // Memoru allocation failed
    }

    // Read a line from standard input
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // Free memory if reading fails
        return NULL;
    }

    return buf; // Return the buffer containing the line read
}