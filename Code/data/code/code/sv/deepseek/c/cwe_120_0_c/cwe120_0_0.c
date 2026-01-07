#include <string.h>
#include <stdio.h>

void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Kontrollera att bufferten är giltig och tillräckligt stor
    if (buffer == NULL || buffer_size <= 0) {
        return;
    }
    
    // Kontrollera att användarnamnet är giltigt
    if (userName == NULL || userName_size <= 0) {
        // Om användarnamnet är ogiltigt, skriv ett generellt meddelande
        snprintf(buffer, buffer_size, "Grattis!");
        return;
    }
    
    // Beräkna den maximala längden för användarnamnet som kan användas
    // "Grattis, " är 9 tecken, "!" är 1 tecken, och null-terminator är 1 tecken
    int max_user_name_length = buffer_size - 11; // 9 + 1 + 1 = 11
    
    // Om bufferten är för liten för ens det grundläggande meddelandet
    if (max_user_name_length < 0) {
        // Fyll bufferten med en tom sträng för säkerhets skull
        buffer[0] = '\0';
        return;
    }
    
    // Begränsa användarnamnets längd om det är för långt
    int actual_user_name_length = userName_size;
    if (actual_user_name_length > max_user_name_length) {
        actual_user_name_length = max_user_name_length;
    }
    
    // Kopiera "Grattis, " till bufferten
    strncpy(buffer, "Grattis, ", buffer_size);
    
    // Lägg till användarnamnet
    // Vi använder strncat för att undvika buffer overflow
    // Först säkerställer vi att bufferten är null-terminerad
    if (actual_user_name_length > 0) {
        // Kontrollera hur mycket utrymme som finns kvar
        int current_length = strlen(buffer);
        int remaining_space = buffer_size - current_length - 1; // -1 för null-terminator
        
        if (remaining_space > 0) {
            // Kopiera användarnamnet med säker längdbegränsning
            int copy_length = actual_user_name_length;
            if (copy_length > remaining_space) {
                copy_length = remaining_space;
            }
            
            // Kopiera användarnamnet manuellt för att undvika strncat-problem
            for (int i = 0; i < copy_length; i++) {
                buffer[current_length + i] = userName[i];
            }
            buffer[current_length + copy_length] = '\0';
        }
    }
    
    // Lägg till "!" på slutet om det finns plats
    int current_length = strlen(buffer);
    if (current_length < buffer_size - 1) {
        buffer[current_length] = '!';
        buffer[current_length + 1] = '\0';
    } else if (buffer_size > 1) {
        // Om bufferten är full, ersätt sista tecknet med '!'
        buffer[buffer_size - 2] = '!';
        buffer[buffer_size - 1] = '\0';
    }
}