#include <stdio.h>

/**
 * @brief Removes trailing whitespace characters from a string in place.
 *
 * This function modifies the input string by removing all whitespace characters
 * (such as spaces, tabs, and newlines) from the end of the string. The characters
 * in the string are shifted to ensure the string ends immediately after the last
 * non-whitespace character.
 *
 * @param str A pointer to the string from which trailing whitespace will be removed.
 */
void trim_spaces(char* str) {
    if (str == NULL) {
        return; // Handle NULL pointer
    }

    // Find the length of the string
    char* end = str;
    while (*end) {
        end++;
    }
    
    // Move back to the last character
    end--;

    // Remove trailing whitespace
    while (end >= str && (*end == ' ' || *end == '\t' || *end == '\n')) {
        end--;
    }

    // Null-terminate the string after the last non-whitespace character
    *(end + 1) = '\0';
}