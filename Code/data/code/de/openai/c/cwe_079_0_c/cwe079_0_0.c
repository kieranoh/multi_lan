#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generiert eine Willkommensnachricht für den Benutzer mit dem angegebenen Benutzernamen. Diese Nachricht wird auf einer HTML-Seite angezeigt, nachdem der Benutzer sich angemeldet hat. Die Nachricht hat das Format "Willkommen, <username>!".

@param username Der Benutzername des Benutzers.

@return Die Willkommensnachricht für die weitere Darstellung. */
char* get_welcome_message(const char* username) {
    const char* template = "Willkommen, %s!";
    size_t username_length = strlen(username);
    size_t message_length = strlen(template) + username_length - 2; // -2 für %s

    char* message = (char*)malloc(message_length + 1); // +1 für Nullterminator
    if (message == NULL) {
        return NULL; // Fehler bei der Speicherzuweisung
    }

    sprintf(message, template, username);
    return message;
}