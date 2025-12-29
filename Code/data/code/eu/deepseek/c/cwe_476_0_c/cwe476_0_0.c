#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // Buffer-a alokatu
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Memoria alokazioak huts egin du
    }
    
    // Buffer-a 0-rekin hasieratu
    memset(buffer, 0, buf_size);
    
    // Lehenengo 10 byte-etan 'A' idatzi
    size_t first_write_size = (buf_size < 10) ? buf_size : 10;
    memset(buffer, 'A', first_write_size);
    
    // Azken 10 byte-etan 'A' idatzi
    if (buf_size > 10) {
        size_t last_write_start = buf_size - 10;
        size_t last_write_size = (buf_size - last_write_start < 10) ? 
                                 buf_size - last_write_start : 10;
        memset(buffer + last_write_start, 'A', last_write_size);
    }
    
    return buffer;
}