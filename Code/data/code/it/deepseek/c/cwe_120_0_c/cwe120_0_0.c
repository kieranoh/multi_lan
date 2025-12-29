#include <string.h>
#include <stdio.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Calcola la lunghezza massima disponibile per il messaggio
    // Sottraiamo 1 per il terminatore nullo
    int available_size = buffer_size - 1;
    
    // Verifica se il buffer è valido e ha dimensione sufficiente
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        if (buffer != NULL && buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    // Costruisci il messaggio di base
    const char *message_prefix = "Congratulazioni, ";
    const char *message_suffix = "!";
    
    // Calcola la lunghezza totale richiesta
    int prefix_len = (int)strlen(message_prefix);
    int suffix_len = (int)strlen(message_suffix);
    
    // Usa userName_size se fornito, altrimenti calcola la lunghezza di userName
    int name_len;
    if (userName_size > 0) {
        name_len = userName_size;
    } else {
        name_len = (int)strlen(userName);
    }
    
    int total_len = prefix_len + name_len + suffix_len;
    
    // Se il messaggio è troppo lungo per il buffer, tronca il nome utente
    if (total_len > available_size) {
        // Calcola quanto spazio abbiamo per il nome utente
        int max_name_len = available_size - prefix_len - suffix_len;
        
        if (max_name_len > 0) {
            // Copia il prefisso
            strncpy(buffer, message_prefix, buffer_size);
            buffer[buffer_size - 1] = '\0'; // Assicura terminazione
            
            // Copia il nome utente (troncato se necessario)
            int current_len = (int)strlen(buffer);
            int remaining = buffer_size - current_len - 1; // -1 per il suffisso
            
            if (remaining > 0) {
                int copy_len = (name_len < remaining) ? name_len : remaining;
                strncat(buffer, userName, copy_len);
                buffer[buffer_size - 1] = '\0'; // Assicura terminazione
            }
            
            // Aggiungi il suffisso se c'è spazio
            current_len = (int)strlen(buffer);
            if (current_len < buffer_size - 1) {
                strcat(buffer, message_suffix);
            }
        } else {
            // Non c'è spazio nemmeno per il messaggio base
            buffer[0] = '\0';
        }
    } else {
        // C'è spazio sufficiente per il messaggio completo
        strcpy(buffer, message_prefix);
        strncat(buffer, userName, name_len);
        strcat(buffer, message_suffix);
    }
    
    // Assicura che il buffer sia sempre terminato correttamente
    buffer[buffer_size - 1] = '\0';
}