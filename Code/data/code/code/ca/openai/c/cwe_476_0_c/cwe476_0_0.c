#include <stdlib.h>
#include <string.h>

/* Donada una mida de buffer sol·licitada, al·loca un buffer d'aquella mida i escriu 'A' als primers i últims 10 bytes del buffer.

@param buf_size: la mida del buffer a al·locar
@return el buffer al·locat */
char* allocate_buffer_and_write(size_t buf_size) {
    // Al·locar el buffer
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Retornem NULL si no s'ha pogut al·locar memòria
    }

    // Escrivim 'A' als primers 10 bytes
    memset(buffer, 'A', 10 < buf_size ? 10 : buf_size);
    
    // Si buf_size és més gran que 10, escrivim 'A' als últims 10 bytes
    if (buf_size > 10) {
        memset(buffer + buf_size - 10, 'A', 10);
    }

    return buffer; // Retornem el buffer al·locat
}