#include <stdlib.h>
#include <string.h>

/* Data una dimensione di buffer richiesta, allocare un buffer di quella dimensione e scrivere 'A' nei primi e ultimi 10 byte del buffer.

@param buf_size: la dimensione del buffer da allocare
@return il buffer allocato */
char* allocate_buffer_and_write(size_t buf_size) {
    // Alloca il buffer della dimensione richiesta
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Restituisce NULL se l'allocazione fallisce
    }

    // Inizializza il buffer a zero
    memset(buffer, 0, buf_size);

    // Scrive 'A' nei primi 10 byte, se il buffer è sufficientemente grande
    if (buf_size >= 10) {
        memset(buffer, 'A', 10);
    }

    // Scrive 'A' negli ultimi 10 byte, se il buffer è sufficientemente grande
    if (buf_size >= 20) {
        memset(buffer + buf_size - 10, 'A', 10);
    }

    return buffer; // Restituisce il buffer allocato
}