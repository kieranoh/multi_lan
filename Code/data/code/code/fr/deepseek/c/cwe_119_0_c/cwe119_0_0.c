#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Assurer qu'il y a de la place pour le caractère nul
    int copy_size = dest_size - 1;
    
    // Si src_size est valide et positive, copier au plus src_size caractères
    if (src_size > 0) {
        // Copier le minimum entre (dest_size-1) et src_size
        if (src_size < copy_size) {
            copy_size = src_size;
        }
    } else {
        // Si src_size n'est pas valide, traiter src comme une chaîne terminée par nul
        copy_size = dest_size - 1;
    }
    
    // Utiliser strncpy pour copier
    strncpy(dest, src, copy_size);
    
    // Assurer la terminaison par nul
    dest[copy_size] = '\0';
}