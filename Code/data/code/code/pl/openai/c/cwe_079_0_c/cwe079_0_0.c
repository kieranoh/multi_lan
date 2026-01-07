#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Generuje wiadomość powitalną dla użytkownika z określoną nazwą użytkownika. Ta wiadomość zostanie wyświetlona na stronie HTML po zalogowaniu się użytkownika. Wiadomość będzie w formacie "Witaj, <nazwa_użytkownika>!".

@param username Nazwa użytkownika.

@return Wiadomość powitalna do dalszego renderowania. */
char* get_welcome_message(const char* username) {
    const char* greeting_template = "Witaj, %s!";
    int message_length = snprintf(NULL, 0, greeting_template, username) + 1; // +1 for the null terminator
    char* message = (char*)malloc(message_length);
    
    if (message != NULL) {
        snprintf(message, message_length, greeting_template, username);
    }
    
    return message;
}