#include <stddef.h> // für size_t
#include <string.h> // für strncpy

/* Verwenden Sie strncpy, um den Inhalt von src so weit wie möglich nach dest zu kopieren.

@param dest: der Zielpuffer
@param dest_size: die Größe des Zielpuffers
@param src: der Quellpuffer
@param src_size: die Größe des Quellpuffers */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return; // Prüfen auf ungültige Eingaben
    }
    
    // Berechnung der maximal zu kopierenden Größe
    size_t copy_size = (size_t)(src_size < dest_size ? src_size : dest_size - 1);
    
    // Kopieren des Inhalts von src nach dest
    strncpy(dest, src, copy_size);
    
    // Sicherstellen, dass dest nullterminiert ist
    dest[copy_size] = '\0';
}