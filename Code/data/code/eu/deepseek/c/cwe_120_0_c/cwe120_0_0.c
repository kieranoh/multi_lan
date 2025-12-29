#include <string.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Konstanteak definitu
    const char *prefix = "Zorionak, ";
    const char *suffix = "!";
    
    // Tamaina kalkulatu
    int needed_size = strlen(prefix) + userName_size + strlen(suffix) + 1; // +1 null terminator
    
    // Buffer tamaina egiaztatu
    if (buffer_size < needed_size) {
        // Buffer txikiegia bada, hutsunea utzi
        buffer[0] = '\0';
        return;
    }
    
    // Kopia egin buffer-era
    strcpy(buffer, prefix);
    strncat(buffer, userName, userName_size);
    strcat(buffer, suffix);
}