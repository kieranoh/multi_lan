#include <string.h>

/* usa strncpy para copiar el contenido de src a dest tanto como sea posible

@param dest: el búfer de destino
@param dest_size: el tamaño del búfer de destino
@param src: el búfer de origen
@param src_size: el tamaño del búfer de origen */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return; // Manejo de errores, si los punteros son nulos o el tamaño es inválido
    }

    // Usar strncpy para copiar el contenido de src a dest
    strncpy(dest, src, dest_size - 1); // Dejar espacio para el terminador nulo
    dest[dest_size - 1] = '\0'; // Asegurar que dest esté null-terminado
}