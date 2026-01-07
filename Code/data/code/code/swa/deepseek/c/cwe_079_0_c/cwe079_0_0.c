#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_welcome_message(const char* username) {
    // Prüfe auf NULL-Pointer
    if (username == NULL) {
        return NULL;
    }
    
    // Länge des Präfix "Willkommen, " berechnen
    const char* prefix = "Willkommen, ";
    const char* suffix = "!";
    
    // Gesamtlänge berechnen: prefix + username + suffix + Null-Terminator
    size_t prefix_len = strlen(prefix);
    size_t username_len = strlen(username);
    size_t suffix_len = strlen(suffix);
    size_t total_len = prefix_len + username_len + suffix_len + 1;
    
    // Speicher für die Nachricht allokieren
    char* message = (char*)malloc(total_len * sizeof(char));
    if (message == NULL) {
        return NULL; // Speicherallokation fehlgeschlagen
    }
    
    // Nachricht zusammensetzen
    strcpy(message, prefix);
    strcat(message, username);
    strcat(message, suffix);
    
    return message;
}