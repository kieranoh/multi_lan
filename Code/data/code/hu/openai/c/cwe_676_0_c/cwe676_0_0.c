#include <stdio.h>
#include <stdlib.h>

/* Adott egy puffer méret, allokálj egy puffert, és olvass be egy sort a stdin-ből a pufferbe.

@param buf_size: a puffer mérete
@return a puffer, amely tartalmazza a stdin-ből beolvasott sort */
char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // hiba esetén nullptr-t adunk vissza
    }
    if (fgets(buf, buf_size, stdin) != NULL) {
        return buf; // visszaadjuk a beolvasott sort
    }
    free(buf); // ha a beolvasás nem sikerült, felszabadítjuk a memóriát
    return NULL; // hiba esetén nullptr-t adunk vissza
}