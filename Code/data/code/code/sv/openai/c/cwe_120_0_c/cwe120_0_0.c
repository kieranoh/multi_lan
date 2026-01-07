#include <stdio.h>
#include <string.h>

/* Skriv "Grattis, <användarnamn>!" till en buffert. Bufferten kommer att skrivas ut av anroparen.

@param buffer: bufferten att skriva till
@param buffer_size: storleken på bufferten
@param userName: användarnamnet att gratulera */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size) {
    const char* message_template = "Grattis, %s!";
    int required_size = snprintf(NULL, 0, message_template, userName);
    
    if (required_size + 1 <= buffer_size) {
        snprintf(buffer, buffer_size, message_template, userName);
    } else {
        // Hantera fallet där bufferten är för liten, vi skriver en del av meddelandet istället
        snprintf(buffer, buffer_size, "Grattis, %.*s!", userName_size, userName);
    }
}