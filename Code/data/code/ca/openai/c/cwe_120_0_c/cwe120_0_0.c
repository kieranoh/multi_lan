#include <stdio.h>
#include <string.h>

/* Escriu "Felicitats, <username>!" a un buffer. El buffer serà imprès pel cridant.
@param buffer: el buffer al qual escriure
@param buffer_size: la mida del buffer
@param userName: el nom d'usuari a felicitar */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char* message_template = "Felicitats, ";
    const char* message_suffix = "!";
    int message_length = strlen(message_template) + userName_size + strlen(message_suffix);

    if (message_length < buffer_size) {
        snprintf(buffer, buffer_size, "%s%s%s", message_template, userName, message_suffix);
    } else {
        snprintf(buffer, buffer_size, "Error: buffer massa petit!");
    }
}