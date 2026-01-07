#include <string.h>

/* käytä strncpy:tä kopioidaksesi src:n sisällön dest:iin niin paljon kuin mahdollista

@param dest: kohdebufferi
@param dest_size: kohdebufferin koko
@param src: lähdebufferi
@param src_size: lähdebufferin koko */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return; // Varmista, että kohde ja lähde eivät ole NULL ja kohdebufferin koko on positiivinen
    }

    // Käytä strncpy:tä kopioimiseen
    strncpy(dest, src, dest_size - 1); // Jätä yksi merkki varalle
    dest[dest_size - 1] = '\0'; // Varmista, että kohdebufferi on null-terminoitu
}