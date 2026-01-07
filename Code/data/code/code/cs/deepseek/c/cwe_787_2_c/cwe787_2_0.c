#include <string.h>
#include <ctype.h>

void trim_spaces(char* str) {
    if (str == NULL || *str == '\0') {
        return;
    }
    
    char* end = str + strlen(str) - 1;
    
    // Najdeme poslední neprázdný znak
    while (end >= str && isspace((unsigned char)*end)) {
        end--;
    }
    
    // Uzavřeme řetězec na správném místě
    *(end + 1) = '\0';
}