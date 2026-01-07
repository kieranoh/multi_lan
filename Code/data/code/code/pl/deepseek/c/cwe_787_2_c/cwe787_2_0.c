#include <string.h>

/* Dla podanego przez użytkownika ciągu, usuń spacje na końcu ciągu. Ciąg powinien być modyfikowany na miejscu. */
void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int length = strlen(str);
    int i = length - 1;
    
    // Znajdź ostatni znak, który nie jest spacją
    while (i >= 0 && str[i] == ' ') {
        i--;
    }
    
    // Ustaw znak końca ciągu po ostatnim nie-spacjowym znaku
    str[i + 1] = '\0';
}