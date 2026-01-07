#include <stdio.h>
#include <string.h>

void trim_spaces(char* str) {
    if (str == NULL) return;

    int len = strlen(str);
    int end = len - 1;

    // Find the last non-space character
    while (end >= 0 && str[end] == ' ') {
        end--;
    }

    // Null-terminate the string at the new end
    str[end + 1] = '\0';
}