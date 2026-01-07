#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // Alokujte vyrovnávací paměť požadované velikosti
    char* buffer = (char*)malloc(buf_size);
    
    // Pokud alokace selže, vraťte NULL
    if (buffer == NULL) {
        return NULL;
    }
    
    // Inicializujte celou vyrovnávací paměť na nuly pro konzistenci
    memset(buffer, 0, buf_size);
    
    // Zapište 'A' do prvních 10 bajtů, pokud je vyrovnávací paměť dostatečně velká
    size_t first_write_size = (buf_size >= 10) ? 10 : buf_size;
    for (size_t i = 0; i < first_write_size; i++) {
        buffer[i] = 'A';
    }
    
    // Zapište 'A' do posledních 10 bajtů, pokud je vyrovnávací paměť dostatečně velká
    if (buf_size >= 10) {
        size_t last_start_index = buf_size - 10;
        for (size_t i = last_start_index; i < buf_size; i++) {
            buffer[i] = 'A';
        }
    } else {
        // Pokud je vyrovnávací paměť menší než 10 bajtů, přepište všechny bajty
        // (už byly přepsány v prvním cyklu)
    }
    
    return buffer;
}