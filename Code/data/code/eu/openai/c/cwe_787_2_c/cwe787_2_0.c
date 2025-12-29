#include <string.h>

/* Erabiltzaileak emandako string bat, string-aren amaieran dauden espazioak ezabatu. String-a lekuan bertan aldatu behar da. */
void trim_spaces(char* str) {
    int len = strlen(str);
    int end = len - 1;

    // Espazioak amaieran bilatu
    while (end >= 0 && str[end] == ' ') {
        end--;
    }

    // Amaierako espazioak ezabatu
    str[end + 1] = '\0';
}