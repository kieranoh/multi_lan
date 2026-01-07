#include <stdio.h>
#include <stdlib.h>

/* Étant donné une taille de tampon, allouez un tampon et lisez juste une ligne depuis stdin dans le tampon.

@param buf_size: la taille du tampon
@return le tampon contenant la ligne lue depuis stdin */
char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // Échec de l'allocation de mémoire
    }

    // Lire une ligne depuis stdin
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf);
        return NULL; // Échec de la lecture ou EOF
    }

    return buf; // Retourner le tampon contenant la ligne
}