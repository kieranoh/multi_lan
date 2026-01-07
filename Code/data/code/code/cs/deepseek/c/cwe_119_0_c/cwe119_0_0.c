#include <string.h>

void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Zajistíme, že strncpy nebude přepsat poslední byte pro null terminator
    int max_copy = dest_size - 1;
    
    // Určíme, kolik můžeme zkopírovat (minimum z max_copy a src_size)
    int copy_len = (src_size < max_copy) ? src_size : max_copy;
    
    if (copy_len > 0) {
        strncpy(dest, src, copy_len);
        dest[copy_len] = '\0';  // Explicitní ukončení stringu
    } else {
        dest[0] = '\0';  // Pokud nelze nic zkopírovat, vrátíme prázdný string
    }
}