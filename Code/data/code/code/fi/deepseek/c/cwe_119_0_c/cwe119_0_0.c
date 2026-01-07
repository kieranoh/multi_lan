#include <string.h>

/* käytä strncpy:tä kopioidaksesi src:n sisällön dest:iin niin paljon kuin mahdollista

@param dest: kohdebufferi
@param dest_size: kohdebufferin koko
@param src: lähdebufferi
@param src_size: lähdebufferin koko */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Varmistetaan, että kopioidaan vain niin paljon kuin mahtuu kohdebufferiin
    // (jätetään tilaa null-terminaattorille)
    int copy_size = dest_size - 1;
    
    // Jos lähdebufferia on vähemmän kuin kopioitava määrä, rajoitetaan sitä
    if (src_size < copy_size) {
        copy_size = src_size;
    }
    
    // Kopioidaan data strncpy:llä
    strncpy(dest, src, copy_size);
    
    // Varmistetaan, että kohdebufferi on null-terminoitu
    dest[copy_size] = '\0';
}