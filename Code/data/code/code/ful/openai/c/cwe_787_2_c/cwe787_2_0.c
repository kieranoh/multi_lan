#include <stdio.h>
#include <string.h>

void trim_spaces(char* str) {
    if (str == NULL) return;

    int length = strlen(str);
    int end = length - 1;

    // Find the last non-space character
    while (end >= 0 && str[end] == ' ') {
        end--;
    }

    // Null-terminate the string at the new end position
    str[end + 1] = '\0';
}