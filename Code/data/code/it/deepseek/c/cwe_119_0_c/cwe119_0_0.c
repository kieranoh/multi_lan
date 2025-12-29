#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Assicurarsi che dest_size sia positiva e ci sia spazio per il terminatore nullo
    int max_copy_size = dest_size - 1;
    
    // Se src_size è non positiva, trattiamo src come stringa terminata da null
    if (src_size <= 0) {
        // Copia al massimo dest_size-1 caratteri da src, assicurandosi il terminatore nullo
        strncpy(dest, src, max_copy_size);
        dest[max_copy_size] = '\0';
    } else {
        // Determina quanti caratteri copiare (il minimo tra max_copy_size e src_size)
        int copy_len = max_copy_size < src_size ? max_copy_size : src_size;
        
        // Usa strncpy per copiare esattamente copy_len caratteri
        strncpy(dest, src, copy_len);
        dest[copy_len] = '\0';
    }
}