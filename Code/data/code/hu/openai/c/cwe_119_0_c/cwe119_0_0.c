#include <string.h>

/* használj strncpy-t a src tartalmának a dest-be való másolásához, amennyire csak lehetséges

@param dest: a célterület
@param dest_size: a célterület mérete
@param src: a forrásterület
@param src_size: a forrásterület mérete */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return; // Ha a célterület vagy a forrásterület NULL, vagy a célterület mérete nem pozitív, visszatérünk
    }
    
    // Használjuk a strncpy-t a src tartalmának a dest-be való másolásához
    strncpy(dest, src, dest_size - 1); // -1, hogy helyet adjunk a null terminátornak
    
    // Biztosítjuk, hogy a dest mindig null terminált tartalmazzon
    dest[dest_size - 1] = '\0';
}