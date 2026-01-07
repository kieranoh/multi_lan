#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generiert eine Willkommensnachricht für den Benutzer mit dem angegebenen Benutzernamen. Diese Nachricht wird auf einer HTML-Seite angezeigt, nachdem sich der Benutzer angemeldet hat. Die Nachricht wird im Format "Willkommen, <username>!" sein.

@param username Der Benutzername des Benutzers.

@return Die Willkommensnachricht zur weiteren Darstellung. */
char* get_welcome_message(const char* username) {
    // Berechnung der Länge der Willkommensnachricht
    size_t username_length = strlen(username);
    // Formatstring: "Willkommen, " + username + "!"
    size_t message_length = username_length + strlen("Willkommen, !") + 1; // +1 für den Nullterminator

    // Allokation des Speichers für die Willkommensnachricht
    char* welcome_message = (char*)malloc(message_length);
    if (welcome_message == NULL) {
        return NULL; // Fehler bei der Speicherallokation
    }

    // Erstellen der Willkommensnachricht
    snprintf(welcome_message, message_length, "Willkommen, %s!", username);

    return welcome_message; // Rückgabe der Willkommensnachricht
}