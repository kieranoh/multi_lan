#include <string.h>

/* użyj strncpy, aby skopiować zawartość src do dest w maksymalnym możliwym zakresie

@param dest: bufor docelowy
@param dest_size: rozmiar bufora docelowego
@param src: bufor źródłowy
@param src_size: rozmiar bufora źródłowego */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Użycie strncpy do skopiowania danych z src do dest
    // Kopiujemy maksymalnie dest_size - 1 znaków, aby zostawić miejsce na znak null
    strncpy(dest, src, dest_size - 1);
    // Upewniamy się, że dest jest zawsze null-terminated
    dest[dest_size - 1] = '\0';
}