#include <stdio.h>
#include <string.h>

/*
Napiši "Čestitam, <username>!" u bafer. Bafer će biti odštampan od strane pozivaoca.

@param buffer: bafer u koji se piše
@param buffer_size: veličina bafera
@param userName: korisničko ime koje se čestita 
*/
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    const char* message_format = "Čestitam, %s!";
    int required_size = snprintf(NULL, 0, message_format, userName) + 1; // +1 for null terminator

    if (required_size > buffer_size) {
        // Not enough space in buffer
        return;
    }

    snprintf(buffer, buffer_size, message_format, userName);
}