#include <stdio.h>

void trim_spaces(char* str) {
    if (str == NULL) return; // Check for NULL pointer

    // Find the length of the string
    char *end = str;
    while (*end) {
        end++;
    }
    end--; // Move to the last character

    // Remove trailing spaces
    while (end >= str && *end == ' ') {
        end--;
    }

    // Null-terminate the string after the last non-space character
    *(end + 1) = '\0';
}