#include <stdio.h>
#include <string.h>

/* Schreibe "Herzlichen Glückwunsch, <username>!" in einen Puffer. Der Puffer wird vom Aufrufer ausgegeben.

@param buffer: der Puffer, in den geschrieben werden soll
@param buffer_size: die Größe des Puffers
@param userName: der Benutzername, den es zu gratulieren gilt */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char *message_prefix = "Herzlichen Glückwunsch, ";
    const char *message_suffix = "!";
    int total_length = strlen(message_prefix) + userName_size + strlen(message_suffix);

    if (total_length < buffer_size) {
        snprintf(buffer, buffer_size, "%s%s%s", message_prefix, userName, message_suffix);
    } else {
        // Wenn der Puffer nicht groß genug ist, wird eine Fehlermeldung geschrieben.
        snprintf(buffer, buffer_size, "Fehler: Puffer zu klein.");
    }
}