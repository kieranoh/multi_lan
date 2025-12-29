#include <stdlib.h>
#include <string.h>

/* Dada una solicitud de tamaño de búfer, asigna un búfer de ese tamaño y escribe 'A' en los primeros y últimos 10 bytes del búfer.

@param buf_size: el tamaño del búfer a asignar
@return el búfer asignado */
char* allocate_buffer_and_write(size_t buf_size) {
    // Asigna el búfer
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Retorna NULL si la asignación falla
    }

    // Limpia el búfer
    memset(buffer, 0, buf_size);

    // Escribe 'A' en los primeros 10 bytes
    size_t write_size = buf_size < 10 ? buf_size : 10;
    memset(buffer, 'A', write_size);

    // Escribe 'A' en los últimos 10 bytes
    if (buf_size > 10) {
        memset(buffer + buf_size - 10, 'A', 10);
    }

    return buffer;
}