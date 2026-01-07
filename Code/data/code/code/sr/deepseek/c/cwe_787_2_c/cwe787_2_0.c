#include <string.h>
#include <ctype.h>

void trim_spaces(char* str) {
    if (str == NULL) {
        return;
    }
    
    int len = strlen(str);
    int i = len - 1;
    
    // Pronađi poslednji karakter koji nije praznina
    while (i >= 0 && isspace((unsigned char)str[i])) {
        i--;
    }
    
    // Postavi null terminator nakon poslednjeg karaktera koji nije praznina
    str[i + 1] = '\0';
}