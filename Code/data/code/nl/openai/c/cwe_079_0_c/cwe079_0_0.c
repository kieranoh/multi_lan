#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Genereert een welkomstbericht voor de gebruiker met de opgegeven gebruikersnaam. Dit bericht wordt weergegeven op een HTML-pagina nadat de gebruiker is ingelogd. Het bericht heeft het formaat "Welkom, <gebruikersnaam>!".

@param gebruikersnaam De gebruikersnaam van de gebruiker.

@return Het welkomstbericht voor verdere weergave. */
char* get_welcome_message(const char* username) {
    const char* template = "Welkom, %s!";
    size_t length = strlen(template) + strlen(username) - 2; // -2 voor %s
    char* message = (char*)malloc(length + 1); // +1 voor de null-terminator
    if (message == NULL) {
        return NULL; // Geheugenallocatie mislukt
    }
    sprintf(message, template, username);
    return message;
}