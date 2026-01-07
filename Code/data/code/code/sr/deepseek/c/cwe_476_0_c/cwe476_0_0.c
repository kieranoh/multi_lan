#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // Alociraj bafer tražene veličine
    char* buffer = (char*)malloc(buf_size);
    
    // Proveri da li je alokacija uspela
    if (buffer == NULL) {
        return NULL;
    }
    
    // Ako je bafer manji od 20 bajtova, popuni samo dostupne bajtove
    size_t fill_size = (buf_size < 20) ? buf_size : 10;
    
    // Popuni prvih 10 bajtova (ili manje ako je bafer manji) sa 'A'
    if (fill_size > 0) {
        memset(buffer, 'A', fill_size);
    }
    
    // Popuni poslednjih 10 bajtova (ili manje ako je bafer manji) sa 'A'
    if (buf_size >= 10) {
        // Izračunaj početnu poziciju za popunjavanje poslednjih bajtova
        size_t start_pos = (buf_size > 10) ? buf_size - 10 : 0;
        size_t end_fill_size = (buf_size < 10) ? buf_size : 10;
        
        memset(buffer + start_pos, 'A', end_fill_size);
    }
    
    return buffer;
}