#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // Возвращаем NULL в случае ошибки выделения памяти
    }
    
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // Освобождаем память в случае ошибки чтения
        return NULL;
    }

    return buf;
}