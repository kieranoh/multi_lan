#include <string.h>

/* usa strncpy per copiare il contenuto di src in dest il più possibile

@param dest: il buffer di destinazione
@param dest_size: la dimensione del buffer di destinazione
@param src: il buffer sorgente
@param src_size: la dimensione del buffer sorgente */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Calcola il numero di byte da copiare
    int bytes_to_copy = (dest_size < src_size) ? dest_size - 1 : src_size;
    
    // Copia i dati da src a dest usando strncpy
    strncpy(dest, src, bytes_to_copy);
    
    // Assicura che dest sia null-terminato
    dest[bytes_to_copy] = '\0';
}