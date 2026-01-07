#include <string.h>
#include <stdio.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Provera da li su parametri validni
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        if (buffer != NULL && buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    // Ograničavanje userName_size na stvarnu dužinu stringa ako je potrebno
    int actual_userName_len = 0;
    while (actual_userName_len < userName_size && userName[actual_userName_len] != '\0') {
        actual_userName_len++;
    }
    
    // Formiranje poruke
    const char *prefix = "Čestitam, ";
    const char *suffix = "!";
    
    // Provera da li će poruka stati u bafer
    int needed_size = strlen(prefix) + actual_userName_len + strlen(suffix) + 1; // +1 za null terminator
    
    if (needed_size > buffer_size) {
        // Ako ne stane, ispisati što više može
        int written = 0;
        
        // Kopirati prefiks
        int prefix_len = strlen(prefix);
        int to_copy = (prefix_len < buffer_size - 1) ? prefix_len : buffer_size - 1;
        strncpy(buffer, prefix, to_copy);
        written += to_copy;
        
        // Kopirati korisničko ime
        if (written < buffer_size - 1) {
            int user_to_copy = actual_userName_len;
            if (written + user_to_copy > buffer_size - 1) {
                user_to_copy = buffer_size - 1 - written;
            }
            strncpy(buffer + written, userName, user_to_copy);
            written += user_to_copy;
        }
        
        // Kopirati sufiks
        if (written < buffer_size - 1) {
            int suffix_len = strlen(suffix);
            int suffix_to_copy = suffix_len;
            if (written + suffix_to_copy > buffer_size - 1) {
                suffix_to_copy = buffer_size - 1 - written;
            }
            strncpy(buffer + written, suffix, suffix_to_copy);
            written += suffix_to_copy;
        }
        
        buffer[written] = '\0';
    } else {
        // Ako stane, formirati kompletnu poruku
        strcpy(buffer, prefix);
        strncat(buffer, userName, actual_userName_len);
        strcat(buffer, suffix);
    }
}