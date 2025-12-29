#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Genereert een welkomstbericht voor de gebruiker met de opgegeven gebruikersnaam. Dit bericht wordt weergegeven op een HTML-pagina nadat de gebruiker is ingelogd. Het bericht heeft het formaat "Welkom, <gebruikersnaam>!".

@param gebruikersnaam De gebruikersnaam van de gebruiker.

@return Het welkomstbericht voor verdere weergave. */
char* get_welcome_message(const char* username) {
    // Controleer of de gebruikersnaam NULL is
    if (username == NULL) {
        // Geef een standaardbericht terug voor NULL gebruikersnaam
        char* default_message = (char*)malloc(12 * sizeof(char));
        if (default_message != NULL) {
            strcpy(default_message, "Welkom, !");
        }
        return default_message;
    }
    
    // Bereken de lengte van het bericht
    // "Welkom, " (8 tekens) + gebruikersnaam + "!" (1 teken) + null-terminator (1 teken)
    size_t username_len = strlen(username);
    size_t message_len = 8 + username_len + 1 + 1;
    
    // Alloceer geheugen voor het bericht
    char* message = (char*)malloc(message_len * sizeof(char));
    if (message == NULL) {
        return NULL; // Geheugentoewijzing mislukt
    }
    
    // Construeer het bericht
    strcpy(message, "Welkom, ");
    strcat(message, username);
    strcat(message, "!");
    
    return message;
}