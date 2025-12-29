#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf != NULL) {
        if (fgets(buf, buf_size, stdin) == NULL) {
            free(buf);
            return NULL; // Lerroa irakurri ez bada, buffer-a askatu
        }
    }
    return buf; // Bufferraren ir contentsa itzuli
}