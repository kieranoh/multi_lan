#include <string.h>

/* Verwenden Sie strncpy, um den Inhalt von src so weit wie möglich nach dest zu kopieren.

@param dest: der Zielpuffer
@param dest_size: die Größe des Zielpuffers
@param src: der Quellpuffer
@param src_size: die Größe des Quellpuffers */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    /* Sicherstellen, dass Platz für Nullterminierung bleibt */
    int max_copy_size = dest_size - 1;
    
    /* Begrenzen der Kopiergröße auf die kleinere von:
       - verfügbarem Platz im Zielpuffer (minus Nullterminierung)
       - Größe des Quellpuffers */
    if (src_size < max_copy_size) {
        max_copy_size = src_size;
    }
    
    /* Kopieren des Inhalts mit strncpy */
    strncpy(dest, src, max_copy_size);
    
    /* Sicherstellen der Nullterminierung */
    dest[max_copy_size] = '\0';
}