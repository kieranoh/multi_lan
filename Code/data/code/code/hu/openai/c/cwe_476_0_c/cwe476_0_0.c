#include <stdlib.h>
#include <string.h>

/* A megadott puffer méretének megfelelően allokálj egy pufferet, és írd az 'A' karaktert a puffer első és utolsó 10 bájtjába.

@param buf_size: a lefoglalni kívánt puffer mérete
@return a lefoglalt puffer */
char* allocate_buffer_and_write(size_t buf_size) {
    if (buf_size < 20) {
        return NULL; // Nem elegendő hely az első és utolsó 10 bájt megírásához
    }

    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Allokálás sikertelen
    }

    memset(buffer, 0, buf_size); // A puffer inicializálása nullákkal

    // 'A' karakter írása az első 10 bájtba
    for (size_t i = 0; i < 10; i++) {
        buffer[i] = 'A';
    }

    // 'A' karakter írása az utolsó 10 bájtba
    for (size_t i = 0; i < 10; i++) {
        buffer[buf_size - 1 - i] = 'A';
    }

    return buffer;
}