#include <string.h>

/* használj strncpy-t a src tartalmának a dest-be való másolásához, amennyire csak lehetséges

@param dest: a célterület
@param dest_size: a célterület mérete
@param src: a forrásterület
@param src_size: a forrásterület mérete */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Megállapítjuk a másolható maximális méretet
    int copy_size;
    if (src_size < 0) {
        // Ha src_size negatív, feltételezzük, hogy src null-terminált string
        copy_size = dest_size - 1; // Helyet hagyunk a null terminátornak
    } else {
        // A másolható méret a kettő közül a kisebb: dest_size-1 vagy src_size
        copy_size = (src_size < dest_size - 1) ? src_size : dest_size - 1;
    }
    
    // strncpy használata a másoláshoz
    strncpy(dest, src, copy_size);
    
    // Biztosítjuk, hogy a string null-terminált legyen
    dest[copy_size] = '\0';
}