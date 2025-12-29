#include <stdlib.h>
#include <string.h>

/* Dla żądanej wielkości bufora, przydziel bufor o tej wielkości i zapisz 'A' w pierwszych i ostatnich 10 bajtach bufora.

@param buf_size: rozmiar bufora do przydzielenia
@return przydzielony bufor */
char* allocate_buffer_and_write(size_t buf_size) {
    if (buf_size < 20) {
        return NULL; // Zwróć NULL, jeśli bufor jest za mały
    }

    char *buffer = (char *)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Zwróć NULL w przypadku błędu alokacji
    }

    memset(buffer, 0, buf_size); // Wyczyść bufor
    memset(buffer, 'A', 10); // Zapisz 'A' w pierwszych 10 bajtach
    memset(buffer + buf_size - 10, 'A', 10); // Zapisz 'A' w ostatnich 10 bajtach

    return buffer; // Zwróć przydzielony bufor
}