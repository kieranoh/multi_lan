#include <stdio.h>
#include <stdlib.h>

char* read_stdin_to_buffer(int buf_size) {
    char* buf = (char*)malloc(buf_size);
    if (buf == NULL) {
        return NULL; // Zwraca NULL w przypadku niepowodzenia alokacji pamięci
    }
    
    // Odczytanie tylko jednej linii z stdin
    if (fgets(buf, buf_size, stdin) == NULL) {
        free(buf); // Zwolnij pamięć, jeśli nie udało się odczytać linii
        return NULL;
    }

    return buf; // Zwraca bufor zawierający odczytaną linię
}