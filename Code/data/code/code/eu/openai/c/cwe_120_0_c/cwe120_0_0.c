#include <stdio.h>
#include <string.h>

/* Idatzi "Zorionak, <username>!" buffer batean. Buffer hori deitzen duenak inprimatuko du.

@param buffer: idazteko buffer-a
@param buffer_size: buffer-aren tamaina
@param userName: zoriontzeko erabiltzaile izena */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Formatua "Zorionak, <username>!" idazteko
    const char* message_format = "Zorionak, %s!";
    int written_length = snprintf(buffer, buffer_size, message_format, userName);
    
    // Egiaztatu idazteko tamaina buffer-aren tamaina baino handiagoa den
    if (written_length >= buffer_size) {
        // Hurrengo pausoa buffered data trukatzea
        buffer[buffer_size - 1] = '\0'; // Azkenik, buffer-a betea izanez gero, bukatu
    }
}