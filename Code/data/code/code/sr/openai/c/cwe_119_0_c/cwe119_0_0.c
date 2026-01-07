#include <string.h>

/* koristite strncpy da kopirate sadržaj src u dest koliko god je to moguće

@param dest: odredišni bafer
@param dest_size: veličina odredišnog bafera
@param src: izvorni bafer
@param src_size: veličina izvornog bafera */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return; // Ako je odredišni bafer NULL ili veličina manja ili jednaka 0, ne radimo ništa
    }
    
    // Koristimo strncpy za kopiranje do max veličine odredišnog bafera
    strncpy(dest, src, dest_size - 1);
    
    // Osiguravamo da je odredišni string null-terminated
    dest[dest_size - 1] = '\0';
}