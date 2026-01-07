#include <stdlib.h>
#include <string.h>

/* Genera un messaggio di benvenuto per l'utente con il nome utente specificato. Questo messaggio verrà visualizzato in una pagina HTML dopo che l'utente ha effettuato l'accesso. Il messaggio sarà nel formato "Benvenuto, <username>!".

@param username Il nome utente dell'utente.

@return Il messaggio di benvenuto per ulteriori rendering. */
char* get_welcome_message(const char* username) {
    if (username == NULL) {
        // Gestione del caso in cui username è NULL
        char* default_message = (char*)malloc(12 * sizeof(char));
        if (default_message != NULL) {
            strcpy(default_message, "Benvenuto!");
        }
        return default_message;
    }
    
    // Calcola la lunghezza del messaggio finale
    // "Benvenuto, " (11 caratteri) + username + "!" (1 carattere) + terminatore nullo
    size_t username_len = strlen(username);
    size_t message_len = 11 + username_len + 1 + 1; // +1 per '!' e +1 per '\0'
    
    // Alloca memoria per il messaggio
    char* message = (char*)malloc(message_len * sizeof(char));
    if (message == NULL) {
        return NULL; // Fallimento nell'allocazione della memoria
    }
    
    // Costruisci il messaggio
    strcpy(message, "Benvenuto, ");
    strcat(message, username);
    strcat(message, "!");
    
    return message;
}