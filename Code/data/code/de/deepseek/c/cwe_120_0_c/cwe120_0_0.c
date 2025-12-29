#include <string.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char *prefix = "Herzlichen Glückwunsch, ";
    const char *suffix = "!";
    
    /* Berechne die benötigte Länge */
    int needed_length = strlen(prefix) + userName_size + strlen(suffix) + 1; /* +1 für Null-Terminator */
    
    /* Sicherstellen, dass der Puffer groß genug ist */
    if (buffer_size < needed_length) {
        /* Wenn der Puffer zu klein ist, schreibe eine Fehlermeldung oder fülle so viel wie möglich */
        strncpy(buffer, "Puffer zu klein", buffer_size - 1);
        buffer[buffer_size - 1] = '\0';
        return;
    }
    
    /* Kopiere den Präfix */
    strcpy(buffer, prefix);
    
    /* Kopiere den Benutzernamen */
    strncat(buffer, userName, userName_size);
    
    /* Füge das Suffix hinzu */
    strcat(buffer, suffix);
}