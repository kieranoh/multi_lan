#include <stdlib.h>
#include <string.h>

/* A megadott puffer méretének megfelelően allokálj egy pufferet, és írd az 'A' karaktert a puffer első és utolsó 10 bájtjába.

@param buf_size: a lefoglalni kívánt puffer mérete
@return a lefoglalt puffer */
char* allocate_buffer_and_write(size_t buf_size) {
    if (buf_size == 0) {
        return NULL;
    }
    
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;
    }
    
    // Töltse ki a puffer első 10 bájtját 'A' karakterrel
    size_t first_write_size = (buf_size < 10) ? buf_size : 10;
    memset(buffer, 'A', first_write_size);
    
    // Ha a puffer elég nagy, töltse ki az utolsó 10 bájtot is
    if (buf_size > 10) {
        size_t last_write_start = buf_size - 10;
        memset(buffer + last_write_start, 'A', 10);
    }
    
    return buffer;
}