#include <stdlib.h>
#include <string.h>

/* Étant donné une taille de tampon demandée, allouez un tampon de cette taille et écrivez 'A' dans les 10 premiers et les 10 derniers octets du tampon.

@param buf_size: la taille du tampon à allouer
@return le tampon alloué */
char* allocate_buffer_and_write(size_t buf_size) {
    // Allouer le tampon
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Retourner NULL en cas d'échec d'allocation
    }

    // Initialiser tous les octets à 0
    memset(buffer, 0, buf_size);

    // Écrire 'A' dans les 10 premiers octets, si la taille le permet
    if (buf_size > 0) {
        size_t first_part_size = buf_size < 10 ? buf_size : 10;
        memset(buffer, 'A', first_part_size);
    }

    // Écrire 'A' dans les 10 derniers octets, si la taille le permet
    if (buf_size > 10) {
        size_t last_part_size = buf_size - 10 < 10 ? buf_size - 10 : 10;
        memset(buffer + buf_size - last_part_size, 'A', last_part_size);
    }

    return buffer;
}