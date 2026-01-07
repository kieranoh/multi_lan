#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Üdvözlő üzenetet generál a megadott felhasználónévvel rendelkező felhasználónak. Ez az üzenet HTML oldalon jelenik meg, miután a felhasználó bejelentkezett. Az üzenet formátuma: "Üdvözöljük, <felhasználónév>!".

@param username A felhasználó felhasználóneve.

@return Az üdvözlő üzenet további megjelenítéshez. */
char* get_welcome_message(const char* username) {
    const char* greeting_template = "Üdvözöljük, %s!";
    // Számítsuk ki a szükséges memória méretét
    size_t message_length = strlen(greeting_template) + strlen(username) - 2; // -2 a %s miatt
    char* message = (char*)malloc(message_length + 1); // +1 a null terminátor miatt

    if (message != NULL) {
        snprintf(message, message_length + 1, greeting_template, username);
    }

    return message;
}