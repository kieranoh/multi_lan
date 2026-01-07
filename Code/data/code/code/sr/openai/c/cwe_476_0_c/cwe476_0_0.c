#include <stdlib.h>
#include <string.h>

/* Na osnovu tražene veličine bafera, alocirajte bafer te veličine i upišite 'A' u prvih i poslednjih 10 bajtova bafera.

@param buf_size: veličina bafera za alokaciju
@return alocirani bafer */
char* allocate_buffer_and_write(size_t buf_size) {
    // Alokacija bafera sa traženom veličinom
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Vraćamo NULL ako alokacija nije uspela
    }

    // Postavljanje prvih 10 bajtova na 'A'
    memset(buffer, 'A', 10);

    // Postavljanje poslednjih 10 bajtova na 'A'
    if (buf_size > 10) {
        memset(buffer + buf_size - 10, 'A', 10);
    }

    return buffer; // Vraćamo alocirani bafer
}