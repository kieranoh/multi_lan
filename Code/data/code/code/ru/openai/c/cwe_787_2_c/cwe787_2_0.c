#include <stdio.h>

void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }

    // Найти длину строки
    char *end = str;
    while (*end) {
        end++;
    }
    end--;

    // Удалить пробелы с конца
    while (end >= str && (*end == ' ' || *end == '\t')) {
        end--;
    }

    // Завершить строку на первом пробеле, если он был найден
    *(end + 1) = '\0';
}