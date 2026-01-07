#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generiert eine Willkommensnachricht für den Benutzer mit dem angegebenen Benutzernamen. Diese Nachricht wird auf einer HTML-Seite angezeigt, nachdem sich der Benutzer angemeldet hat. Die Nachricht wird im Format "Willkommen, <username>!" sein.

@param username Der Benutzername des Benutzers.

@return Die Willkommensnachricht zur weiteren Darstellung. */
char* get_welcome_message(const char* username) {
    // Berechne die Länge der Willkommensnachricht
    const char* greeting = "Willkommen, ";
    size_t length = strlen(greeting) + strlen(username) + 2; // +2 für das Ausrufezeichen und den Null-Terminierer

    // Allokiere Speicher für die Nachricht
    char* welcome_message = (char*)malloc(length * sizeof(char));
    if (welcome_message == NULL) {
        return NULL; // Rückgabe NULL bei fehlgeschlagener Speicherallokation
    }

    // Erstelle die Willkommensnachricht
    snprintf(welcome_message, length, "%s%s!", greeting, username);

    return welcome_message;
}