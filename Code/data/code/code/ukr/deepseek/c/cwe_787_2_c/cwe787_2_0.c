#include <string.h>

void trim_spaces(char* str) {
    if (str == NULL || *str == '\0') {
        return;
    }
    
    char* end = str + strlen(str) - 1;
    
    while (end >= str && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
        end--;
    }
    
    *(end + 1) = '\0';
}