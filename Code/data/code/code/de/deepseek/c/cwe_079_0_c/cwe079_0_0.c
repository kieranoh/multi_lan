#include <stdlib.h>
#include <string.h>

/* Generiert eine Willkommensnachricht für den Benutzer mit dem angegebenen Benutzernamen. Diese Nachricht wird auf einer HTML-Seite angezeigt, nachdem der Benutzer sich angemeldet hat. Die Nachricht hat das Format "Willkommen, <username>!".

@param username Der Benutzername des Benutzers.

@return Die Willkommensnachricht für die weitere Darstellung. */
char* get_welcome_message(const char* username) {
    if (username == NULL) {
        return NULL;
    }
    
    const char* prefix = "Willkommen, ";
    const char* suffix = "!";
    
    size_t username_len = strlen(username);
    size_t prefix_len = strlen(prefix);
    size_t suffix_len = strlen(suffix);
    
    char* message = (char*)malloc(prefix_len + username_len + suffix_len + 1);
    
    if (message == NULL) {
        return NULL;
    }
    
    strcpy(message, prefix);
    strcat(message, username);
    strcat(message, suffix);
    
    return message;
}