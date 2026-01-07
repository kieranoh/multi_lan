#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Genera un messaggio di benvenuto per l'utente con il nome utente specificato. Questo messaggio verrà visualizzato in una pagina HTML dopo che l'utente ha effettuato l'accesso. Il messaggio sarà nel formato "Benvenuto, <username>!".

@param username Il nome utente dell'utente.

@return Il messaggio di benvenuto per ulteriori rendering. */
char* get_welcome_message(const char* username) {
    if (username == NULL) {
        return NULL; // Gestione del caso in cui username sia NULL
    }

    // Calcolo della lunghezza del messaggio finale
    size_t length = strlen(username) + strlen("Benvenuto, !") + 1; // +1 per il carattere di terminazione
    char* message = (char*)malloc(length * sizeof(char));
    
    if (message == NULL) {
        return NULL; // Gestione dell'errore di allocazione
    }

    // Creazione del messaggio di benvenuto
    snprintf(message, length, "Benvenuto, %s!", username);
    return message;
}