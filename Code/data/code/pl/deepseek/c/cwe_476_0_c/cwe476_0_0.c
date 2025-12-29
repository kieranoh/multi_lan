#include <stdlib.h>
#include <string.h>
#include <stddef.h>

char* allocate_buffer_and_write(size_t buf_size) {
    if (buf_size == 0) {
        return NULL;
    }
    
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;
    }
    
    // Wypełnij cały bufor zerami
    memset(buffer, 0, buf_size);
    
    // Zapisz 'A' w pierwszych 10 bajtach
    size_t first_write_size = (buf_size < 10) ? buf_size : 10;
    memset(buffer, 'A', first_write_size);
    
    // Zapisz 'A' w ostatnich 10 bajtach, jeśli bufor jest wystarczająco duży
    if (buf_size > 10) {
        size_t last_write_size = (buf_size < 20) ? (buf_size - 10) : 10;
        memset(buffer + buf_size - last_write_size, 'A', last_write_size);
    }
    
    return buffer;
}