#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL;
    }
    
    // Nur eine Zeile lesen
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf);
        return NULL;
    }
    
    // Entferne möglichen Zeilenumbruch am Ende
    for (int i = 0; i < buf_size; i++) {
        if (buf[i] == '\n') {
            buf[i] = '\0';
            break;
        }
    }
    
    return buf;
}