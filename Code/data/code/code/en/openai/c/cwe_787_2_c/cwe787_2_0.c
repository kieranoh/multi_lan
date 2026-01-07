#include <stdio.h>

void trim_spaces(char* str) {
    if (str == NULL) return; // Check for NULL pointer

    // Find the length of the string
    char *end = str;
    while (*end != '\0') {
        end++;
    }
    end--; // Point to the last character

    // Trim trailing spaces
    while (end >= str && *end == ' ') {
        end--;
    }

    // Null-terminate the string at the new end
    *(end + 1) = '\0';
}