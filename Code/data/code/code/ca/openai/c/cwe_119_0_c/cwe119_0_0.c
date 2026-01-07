#include <stdio.h>
#include <string.h>

/* utilitzeu strncpy per copiar el contingut de src a dest tant com sigui possible

@param dest: el buffer de destinació
@param dest_size: la mida del buffer de destinació
@param src: el buffer font
@param src_size: la mida del buffer font */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Comprovem si la mida del buffer de destinació és vàlida
    if (dest_size <= 0) {
        return; // No podem copiar res si la mida és zero o negativa
    }

    // Utilitzem strncpy per copiar el contingut de src a dest
    // Ens assegurem que no copiem més del que permet la mida de dest
    strncpy(dest, src, dest_size - 1);
    
    // Assegurem que dest sigui null-terminated
    dest[dest_size - 1] = '\0';
}