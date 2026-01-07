#include <stddef.h>

void trim_spaces(char* str) {
    if (str == NULL) return; // Sprawdzenie, czy wskaźnik jest NULL

    size_t length = 0;
    while (str[length] != '\0') { // Oblicz długość ciągu
        length++;
    }

    // Usuwanie spacji z końca ciągu
    while (length > 0 && str[length - 1] == ' ') {
        length--;
    }

    str[length] = '\0'; // Zakończenie ciągu na nowej długości
}