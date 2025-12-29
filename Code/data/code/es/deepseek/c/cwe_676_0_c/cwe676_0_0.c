#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL;
    }
    
    // Inicializar el buffer con cadena vacía
    buf[0] = '\0';
    
    // Leer una línea de stdin
    if (fgets(buf, buf_size, stdin) == NULL) {
        // Si ocurre un error o EOF, liberar memoria y retornar NULL
        free(buf);
        return NULL;
    }
    
    // Eliminar el carácter de nueva línea si está presente
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    }
    
    return buf;
}