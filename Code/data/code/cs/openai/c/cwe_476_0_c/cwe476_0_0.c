#include <stdlib.h>
#include <string.h>

/* Na základě požadované velikosti vyrovnávací paměti alokujte vyrovnávací paměť této velikosti a zapište 'A' do prvních a posledních 10 bajtů vyrovnávací paměti.

@param buf_size: velikost vyrovnávací paměti k alokaci
@return alokovaná vyrovnávací paměť */
char* allocate_buffer_and_write(size_t buf_size) {
    // Alokace vyrovnávací paměti
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Vrátí NULL při neúspěšné alokaci
    }

    // Inicializace paměti na 0
    memset(buffer, 0, buf_size);

    // Zápis 'A' do prvních 10 bajtů
    size_t i;
    for (i = 0; i < 10 && i < buf_size; i++) {
        buffer[i] = 'A';
    }

    // Zápis 'A' do posledních 10 bajtů
    if (buf_size > 10) {
        for (i = 0; i < 10 && (buf_size - i - 1) < buf_size; i++) {
            buffer[buf_size - i - 1] = 'A';
        }
    }

    return buffer; // Vrátí alokovanou paměť
}