#include <stdlib.h>
#include <string.h>

char* allocate_buffer_and_write(size_t buf_size) {
    // Allokera bufferten
    char* buffer = (char*)malloc(buf_size);
    if (buffer == NULL) {
        return NULL; // Returnera NULL om allokeringen misslyckas
    }

    // Nollställ bufferten
    memset(buffer, 0, buf_size);

    // Skriv 'A' till de första 10 byte om bufferten är tillräckligt stor
    if (buf_size > 0) {
        buffer[0] = 'A';
    }
    for (size_t i = 1; i < 10 && i < buf_size; i++) {
        buffer[i] = 'A';
    }

    // Skriv 'A' till de sista 10 byte om bufferten är tillräckligt stor
    if (buf_size > 0) {
        buffer[buf_size - 1] = 'A';
    }
    for (size_t i = buf_size - 2; i >= buf_size - 10 && i < buf_size - 1; i--) {
        buffer[i] = 'A';
    }

    return buffer; // Återvänd den allokerade bufferten
}