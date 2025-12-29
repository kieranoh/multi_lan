#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Asegurar que haya espacio para el carácter nulo de terminación
    int copy_size = dest_size - 1;
    
    // Si src_size es válido, copiar como máximo src_size caracteres
    if (src_size > 0) {
        // Copiar el mínimo entre (dest_size-1) y src_size caracteres
        if (src_size < copy_size) {
            copy_size = src_size;
        }
    }
    
    // Usar strncpy para copiar los caracteres
    strncpy(dest, src, copy_size);
    
    // Asegurar terminación nula
    dest[copy_size] = '\0';
}