#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_welcome_message(const char* username) {
    // Ellenőrizzük, hogy a username nem NULL
    if (username == NULL) {
        char* error_msg = (char*)malloc(20 * sizeof(char));
        if (error_msg != NULL) {
            strcpy(error_msg, "Üdvözöljük, vendég!");
        }
        return error_msg;
    }
    
    // Kiszámoljuk a szükséges memória méretét
    // "Üdvözöljük, " = 12 karakter + username hossza + "!" + null terminátor
    size_t username_len = strlen(username);
    size_t total_len = 12 + username_len + 1 + 1; // +1 a '!'-hez, +1 a null terminátorhoz
    
    // Memória foglalás az üzenetnek
    char* welcome_msg = (char*)malloc(total_len * sizeof(char));
    
    // Ellenőrizzük, hogy sikerült-e a memória foglalás
    if (welcome_msg == NULL) {
        return NULL;
    }
    
    // Üdvözlő üzenet összeállítása
    strcpy(welcome_msg, "Üdvözöljük, ");
    strcat(welcome_msg, username);
    strcat(welcome_msg, "!");
    
    return welcome_msg;
}