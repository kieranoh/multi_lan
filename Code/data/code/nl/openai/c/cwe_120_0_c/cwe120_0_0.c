#include <stdio.h>
#include <string.h>

/* Schrijf "Gefeliciteerd, <username>!" naar een buffer. De buffer zal door de aanroeper worden afgedrukt.

@param buffer: de buffer om naar te schrijven
@param buffer_size: de grootte van de buffer
@param userName: de gebruikersnaam om te feliciteren */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char* message_template = "Gefeliciteerd, %s!";
    int message_length = snprintf(NULL, 0, message_template, userName);
    int total_length = message_length + 1; // +1 for null terminator

    if (total_length > buffer_size) {
        total_length = buffer_size - 1; // leave space for null terminator
    }

    snprintf(buffer, total_length + 1, message_template, userName);
}