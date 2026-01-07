#include <string.h>

/* použijte strncpy k co největšímu zkopírování obsahu src do dest

@param dest: cílový buffer
@param dest_size: velikost cílového bufferu
@param src: zdrojový buffer
@param src_size: velikost zdrojového bufferu */
void copy_to_dest(char* dest, int dest_size, char* src, int src_size) {
    if (dest == NULL || src == NULL || dest_size <= 0) {
        return;
    }
    
    // Zkopírujeme maximálně dest_size - 1 znaků (abychom měli místo na null terminátor)
    strncpy(dest, src, dest_size - 1);
    
    // Zajištění, že dest bude vždy null terminovaný
    dest[dest_size - 1] = '\0';
}