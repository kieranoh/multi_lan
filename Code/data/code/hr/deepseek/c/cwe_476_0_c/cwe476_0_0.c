#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // Ako je veličina bafera manja od 20, ne možemo upisati u prvih i posljednjih 10 bajtova
    if (buf_size < 20) {
        return NULL;
    }
    
    // Alociraj bafer
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;
    }
    
    // Inicijaliziraj cijeli bafer nulama
    memset(buffer, 0, buf_size);
    
    // Upiši 'A' u prvih 10 bajtova
    for (size_t i = 0; i < 10; i++) {
        buffer[i] = 'A';
    }
    
    // Upiši 'A' u posljednjih 10 bajtova
    for (size_t i = buf_size - 10; i < buf_size; i++) {
        buffer[i] = 'A';
    }
    
    return buffer;
}