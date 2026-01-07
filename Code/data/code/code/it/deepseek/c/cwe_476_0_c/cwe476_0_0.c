#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // Alloca il buffer della dimensione richiesta
    char* buffer = (char*)malloc(buf_size);
    
    // Se l'allocazione fallisce, restituisce NULL
    if (buffer == NULL) {
        return NULL;
    }
    
    // Inizializza tutto il buffer a 0 per sicurezza
    memset(buffer, 0, buf_size);
    
    // Scrive 'A' nei primi 10 byte se il buffer è abbastanza grande
    size_t write_size = 10;
    if (buf_size < write_size) {
        write_size = buf_size;  // Se il buffer è più piccolo di 10 byte
    }
    
    for (size_t i = 0; i < write_size; i++) {
        buffer[i] = 'A';
    }
    
    // Scrive 'A' negli ultimi 10 byte se il buffer è abbastanza grande
    if (buf_size >= write_size) {
        for (size_t i = buf_size - write_size; i < buf_size; i++) {
            buffer[i] = 'A';
        }
    }
    
    return buffer;
}