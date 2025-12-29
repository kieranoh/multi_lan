#include <stdio.h>
#include <string.h>

/* Napiši "Čestitamo, <username>!" u bafer. Bafer će ispisati pozivatelj.

@param buffer: bafer u koji se piše
@param buffer_size: veličina bafera
@param userName: korisničko ime koje se čestita */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size) {
    const char *greeting_template = "Čestitamo, ";
    const char *greeting_end = "!";
    
    int required_size = strlen(greeting_template) + userName_size + strlen(greeting_end) + 1; // +1 for null terminator

    if (required_size <= buffer_size) {
        snprintf(buffer, buffer_size, "%s%s%s", greeting_template, userName, greeting_end);
    } else {
        // In case buffer is not enough, we can return an empty string or an error message.
        snprintf(buffer, buffer_size, "Buffer too small");
    }
}