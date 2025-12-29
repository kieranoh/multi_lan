#include <stdlib.h>
#include <string.h>

/* Gegeben eine angeforderte Puffergröße, allokiere einen Puffer dieser Größe und schreibe 'A' in die ersten und letzten 10 Bytes des Puffers.

@param buf_size: die Größe des zu allokierenden Puffers
@return der allokierte Puffer */
char* allocate_buffer_and_write(size_t buf_size) {
    // Allokiere den Puffer
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Rückgabe NULL, wenn die Allokation fehlschlägt
    }

    // Setze die ersten 10 Bytes auf 'A'
    memset(buffer, 'A', 10);

    // Setze die letzten 10 Bytes auf 'A', wenn der Puffer groß genug ist
    if (buf_size >= 10) {
        memset(buffer + buf_size - 10, 'A', 10);
    }

    return buffer; // Rückgabe des allokierten Puffers
}