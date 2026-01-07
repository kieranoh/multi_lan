#include <stdio.h>
#include <stdlib.h>

/* Annetun puskurikoon perusteella, varaa puskuri ja lue vain yksi rivi stdin:stä puskuriin.

@param buf_size: puskurin koko
@return puskuri, joka sisältää stdin:stä luetun rivin */
char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // Tarkistetaan, että muistin varaus onnistui
    }
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // Vapautetaan muisti, jos lukeminen epäonnistuu
        return NULL;
    }
    return buf;
}