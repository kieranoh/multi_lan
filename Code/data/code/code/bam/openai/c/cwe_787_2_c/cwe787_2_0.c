#include <stdio.h>
#include <string.h>

void trim_spaces(char* str) {
    if (str == NULL) return;

    size_t len = strlen(str);
    size_t end = len;

    // Find the last non-space character
    while (end > 0 && (str[end - 1] == ' ' || str[end - 1] == '\t')) {
        end--;
    }

    // Null terminate the string at the new end position
    str[end] = '\0';
}