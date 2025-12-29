#include <string.h>

/* koristite strncpy za kopiranje sadržaja iz src u dest koliko god je to moguće

@param dest: odredišni bafer
@param dest_size: veličina odredišnog bafera
@param src: izvorni bafer
@param src_size: veličina izvornog bafera */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return; // Gracioso vraćanje ako su ulazi neispravni
    }
    
    // Koristi strncpy za kopiranje podataka
    strncpy(dest, src, dest_size - 1);
    
    // Osiguraj da je dest završio sa null karakterom
    dest[dest_size - 1] = '\0';
}