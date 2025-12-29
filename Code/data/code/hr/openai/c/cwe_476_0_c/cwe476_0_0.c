#include <stdlib.h>
#include <string.h>

/* Na temelju zatražene veličine bafera, alocirajte bafer te veličine i upišite 'A' u prvih i posljednjih 10 bajtova bafera.
@param buf_size: veličina bafera za alociranje
@return alocirani bafer */
char* allocate_buffer_and_write(size_t buf_size) {
    // Alocirajte bafer tražene veličine
    char* buffer = (char*)malloc(buf_size);
    
    // Provjerite je li alokacija uspješna
    if (buffer == NULL) {
        return NULL; // Vratite NULL ako alokacija nije uspjela
    }

    // Inicijalizirajte cijeli bafer na 0
    memset(buffer, 0, buf_size);
    
    // Upisite 'A' u prvih 10 bajtova
    for (size_t i = 0; i < 10 && i < buf_size; i++) {
        buffer[i] = 'A';
    }

    // Upisite 'A' u posljednjih 10 bajtova
    for (size_t i = 0; i < 10 && (buf_size - 1 - i) >= 0; i++) {
        buffer[buf_size - 1 - i] = 'A';
    }

    return buffer; // Vratite alocirani bafer
}