#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Genererar ett välkomstmeddelande för användaren med det angivna användarnamnet. Detta meddelande kommer att renderas på en HTML-sida efter att användaren har loggat in. Meddelandet kommer att vara i formatet "Välkommen, <användarnamn>!".

@param användarnamn Användarnamnet för användaren.

@return Välkomstmeddelandet för vidare rendering. */
char* get_welcome_message(const char* username) {
    // Kontrollera om användarnamnet är NULL
    if (username == NULL) {
        return NULL;
    }

    // Beräkna längden på det välkomstmeddelande som ska skapas
    const char* welcome_template = "Välkommen, %s!";
    size_t message_length = strlen(welcome_template) + strlen(username) - 2; // -2 för %s
    char* welcome_message = (char*)malloc(message_length + 1); // +1 för null-terminator

    // Kontrollera om minnesallokeringen lyckades
    if (welcome_message == NULL) {
        return NULL;
    }

    // Skapa det slutliga välkomstmeddelandet
    sprintf(welcome_message, welcome_template, username);

    return welcome_message;
}