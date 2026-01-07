#include <string.h>
#include <stdio.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Provjera valjanosti ulaznih parametara
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        if (buffer != NULL && buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    // Izračunaj koliko prostora treba za poruku
    // "Čestitamo, " + userName + "!" + null terminator
    const char* prefix = "Čestitamo, ";
    const char* suffix = "!";
    
    // Provjeri da li je userName_size valjan; ako nije, koristi strlen
    int actual_userName_size = userName_size;
    if (userName_size < 0) {
        actual_userName_size = strlen(userName);
    }
    
    // Izračunaj ukupnu duljinu poruke
    int total_length = strlen(prefix) + actual_userName_size + strlen(suffix) + 1; // +1 za null terminator
    
    // Provjeri da li bafer ima dovoljno prostora
    if (total_length > buffer_size) {
        // Ako nema dovoljno prostora, ispuni što više možemo
        int prefix_len = strlen(prefix);
        int available_for_name = buffer_size - prefix_len - strlen(suffix) - 1;
        
        if (available_for_name > 0) {
            // Kopiraj prefiks
            strncpy(buffer, prefix, buffer_size);
            buffer[buffer_size - 1] = '\0';
            
            // Kopiraj korisničko ime (koliko god možemo)
            int current_len = strlen(buffer);
            int remaining_space = buffer_size - current_len - 1;
            
            if (remaining_space > 0) {
                strncat(buffer, userName, remaining_space);
                buffer[buffer_size - 1] = '\0';
            }
            
            // Dodaj sufiks ako ima prostora
            current_len = strlen(buffer);
            remaining_space = buffer_size - current_len - 1;
            
            if (remaining_space > 0) {
                strncat(buffer, suffix, remaining_space);
                buffer[buffer_size - 1] = '\0';
            }
        } else {
            // Ako nema prostora ni za prefiks, postavi prazan string
            buffer[0] = '\0';
        }
    } else {
        // Ima dovoljno prostora - napravi kompletnu poruku
        strcpy(buffer, prefix);
        strncat(buffer, userName, actual_userName_size);
        strcat(buffer, suffix);
    }
}