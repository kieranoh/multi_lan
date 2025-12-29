#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // Varaa puskuri
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL;
    }
    
    // Täytä koko puskuri nollalla turvallisuussyistä
    memset(buffer, 0, buf_size);
    
    // Kirjoita 'A' ensimmäiseen 10 tavuun, jos puskuri on tarpeeksi suuri
    size_t write_size = 10;
    if (buf_size < write_size) {
        write_size = buf_size;
    }
    
    for (size_t i = 0; i < write_size; i++) {
        buffer[i] = 'A';
    }
    
    // Kirjoita 'A' viimeiseen 10 tavuun, jos puskuri on tarpeeksi suuri
    if (buf_size >= write_size) {
        for (size_t i = buf_size - write_size; i < buf_size; i++) {
            buffer[i] = 'A';
        }
    }
    
    return buffer;
}