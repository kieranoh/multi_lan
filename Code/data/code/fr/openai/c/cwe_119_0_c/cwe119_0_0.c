#include <stdio.h>
#include <string.h>

/* utilisez strncpy pour copier le contenu de src vers dest autant que possible

@param dest: le tampon de destination
@param dest_size: la taille du tampon de destination
@param src: le tampon source
@param src_size: la taille du tampon source */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Utiliser strncpy pour copier le contenu de src vers dest
    strncpy(dest, src, dest_size - 1); // Réserver un espace pour le caractère nul
    dest[dest_size - 1] = '\0'; // Assurer que dest est null-terminé
}