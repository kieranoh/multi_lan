#include <stdlib.h>
#include <string.h>

/* Annetun puskurikoon perusteella, varaa kyseinen kokoinen puskuri ja kirjoita 'A' puskurin ensimmäiseen ja viimeiseen 10 tavuun.
 
@param buf_size: varattavan puskurin koko
@return varattu puskuri */
char* allocate_buffer_and_write(size_t buf_size) {
    // Varaa muistia annetun kokoiselle puskurille
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Palauta NULL, jos muistinvaraus epäonnistuu
    }
    
    // Alusta puskuri nolliksi
    memset(buffer, 0, buf_size);

    // Kirjoita 'A' puskurin ensimmäisiin 10 tavuun
    for (size_t i = 0; i < 10 && i < buf_size; ++i) {
        buffer[i] = 'A';
    }
    
    // Kirjoita 'A' puskurin viimeiseen 10 tavuun
    for (size_t i = 0; i < 10 && (buf_size - 1 - i) >= 0; ++i) {
        if (buf_size - 1 - i >= 10) {
            buffer[buf_size - 1 - i] = 'A';
        }
    }

    return buffer; // Palauta varattu puskuri
}