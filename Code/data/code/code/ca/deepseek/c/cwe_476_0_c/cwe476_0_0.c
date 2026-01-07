#include <stdlib.h>
#include <string.h>
#include <stddef.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // Al·loca el buffer
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;  // Retorna NULL si l'al·locació falla
    }
    
    // Inicialitza tot el buffer a 0 per seguretat
    memset(buffer, 0, buf_size);
    
    // Escriu 'A' als primers 10 bytes si el buffer és prou gran
    size_t write_size = (buf_size < 10) ? buf_size : 10;
    for (size_t i = 0; i < write_size; i++) {
        buffer[i] = 'A';
    }
    
    // Escriu 'A' als últims 10 bytes si el buffer és prou gran
    if (buf_size >= 10) {
        for (size_t i = buf_size - 10; i < buf_size; i++) {
            buffer[i] = 'A';
        }
    }
    
    return buffer;
}