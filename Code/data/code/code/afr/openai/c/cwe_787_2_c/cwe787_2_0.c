#include <stdio.h>
#include <string.h>

void trim_spaces(char* str) {
    int length = strlen(str);
    
    // Find the last non-space character
    while (length > 0 && str[length - 1] == ' ') {
        length--;
    }
    
    // Null-terminate the string at the new length
    str[length] = '\0';
}