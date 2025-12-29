#include <stddef.h>

void trim_spaces(char* str) {
    if (str == NULL) {
        return; // Pokud je vstupní řetězec NULL, nic nedělej.
    }

    // Najdi délku řetězce
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }

    // Odstraňte koncové mezery
    int end = length - 1;
    while (end >= 0 && (str[end] == ' ' || str[end] == '\t')) {
        end--;
    }

    // Pokud je celková délka řetězce 0 (všechny znaky jsou mezery)
    if (end < 0) {
        str[0] = '\0'; // Nastavte řetězec na prázdný řetězec
        return;
    }

    // Odstraňte přední mezery
    int start = 0;
    while (str[start] == ' ' || str[start] == '\t') {
        start++;
    }

    // Posuňte zbývající znaky na začátek
    for (int i = 0; i <= end - start; i++) {
        str[i] = str[start + i];
    }
    str[end - start + 1] = '\0'; // Přidejte terminátor na konec
}