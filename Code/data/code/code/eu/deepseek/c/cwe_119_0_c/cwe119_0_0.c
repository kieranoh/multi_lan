#include <string.h>

/* strncpy erabiliz, src-ren edukia dest-era kopiatzea ahal den neurrian

@param dest: helmuga buffer-a
@param dest_size: helmuga buffer-aren tamaina
@param src: iturri buffer-a
@param src_size: iturri buffer-aren tamaina */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    // Parametro baliodunak direla ziurtatu
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Kopiatzeko kopuru maximoa kalkulatu
    // dest_size-1 karaktere kopiatu behar ditugu null terminatorrarentzat
    int max_copy = dest_size - 1;
    
    // src_size-ren arabera mugatu kopiatzeko kopurua
    if (src_size >= 0 && src_size < max_copy) {
        max_copy = src_size;
    }
    
    // strncpy erabiliz kopiatu
    strncpy(dest, src, max_copy);
    
    // Null terminatorra ziurtatu
    dest[max_copy] = '\0';
}