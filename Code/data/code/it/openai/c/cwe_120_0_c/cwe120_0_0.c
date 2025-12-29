#include <stdio.h>
#include <string.h>

/* Scrivi "Congratulazioni, <username>!" in un buffer. Il buffer sarà stampato dal chiamante.
@param buffer: il buffer su cui scrivere
@param buffer_size: la dimensione del buffer
@param userName: il nome utente da congratulare */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Controlla che le dimensioni siano valide
    if (buffer == NULL || buffer_size <= 0 || userName == NULL || userName_size <= 0) {
        return;
    }

    // Prepara il messaggio di congratulazioni
    const char *message_format = "Congratulazioni, %s!";
    int message_size = snprintf(NULL, 0, message_format, userName) + 1; // Calcola la dimensione del messaggio

    // Verifica se il buffer è sufficiente
    if (message_size > buffer_size) {
        message_size = buffer_size; // Limita alla dimensione del buffer
    }

    // Scrivi il messaggio nel buffer
    snprintf(buffer, message_size, message_format, userName);
}