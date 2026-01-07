#include <stdlib.h>
#include <string.h>

/* Gegeven een gevraagde buffergrootte, wijs een buffer van die grootte toe en schrijf 'A' naar de eerste en laatste 10 bytes van de buffer.

@param buf_size: de grootte van de buffer die moet worden toegewezen
@return de toegewezen buffer */
char* allocate_buffer_and_write(size_t buf_size) {
    // Wijs de buffer toe
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Retourneer NULL als de toewijzing faalt
    }

    // Schrijf 'A' naar de eerste 10 bytes
    memset(buffer, 'A', buf_size < 10 ? buf_size : 10);

    // Schrijf 'A' naar de laatste 10 bytes, als de buffer groot genoeg is
    if (buf_size > 10) {
        memset(buffer + buf_size - 10, 'A', 10);
    }

    return buffer;
}