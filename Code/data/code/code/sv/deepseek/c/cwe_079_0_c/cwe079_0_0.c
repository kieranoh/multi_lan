#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Genererar ett välkomstmeddelande för användaren med det angivna användarnamnet.
 * Detta meddelande kommer att renderas på en HTML-sida efter att användaren har loggat in.
 * Meddelandet kommer att vara i formatet "Välkommen, <användarnamn>!".
 *
 * @param username Användarnamnet för användaren.
 * @return Välkomstmeddelandet för vidare rendering.
 * @note Anroparen är ansvarig för att frigöra det returnerade minnet med free().
 */
char* get_welcome_message(const char* username) {
    // Kontrollera om användarnamnet är NULL eller tomt
    if (username == NULL || strlen(username) == 0) {
        // Returnera ett standardmeddelande om användarnamnet saknas
        char* default_message = (char*)malloc(20 * sizeof(char));
        if (default_message != NULL) {
            strcpy(default_message, "Välkommen, gäst!");
        }
        return default_message;
    }
    
    // Beräkna längden på det slutliga meddelandet
    // "Välkommen, " (11 tecken) + användarnamn + "!" (1 tecken) + null-terminator (1 tecken)
    size_t username_len = strlen(username);
    size_t message_len = 11 + username_len + 1 + 1; // 11 för "Välkommen, ", 1 för "!", 1 för '\0'
    
    // Allokera minne för meddelandet
    char* message = (char*)malloc(message_len * sizeof(char));
    if (message == NULL) {
        // Minnesallokering misslyckades
        return NULL;
    }
    
    // Konstruera välkomstmeddelandet
    strcpy(message, "Välkommen, ");
    strcat(message, username);
    strcat(message, "!");
    
    return message;
}