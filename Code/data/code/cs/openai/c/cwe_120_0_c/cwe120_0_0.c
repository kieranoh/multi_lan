#include <stdio.h>
#include <string.h>

/* Napište "Gratulujeme, <username>!" do vyrovnávací paměti. Vyrovnávací paměť bude vytištěna volajícím.

@param buffer: vyrovnávací paměť, do které se zapisuje
@param buffer_size: velikost vyrovnávací paměti
@param userName: uživatelské jméno, které se má gratulovat */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Zkontrolujeme, zda je velikost bufferu dostatečná na uloženou zprávu
    const char* message_format = "Gratulujeme, %s!";
    int required_size = snprintf(NULL, 0, message_format, userName) + 1; // +1 pro nulový terminátor

    if (required_size <= buffer_size) {
        snprintf(buffer, buffer_size, message_format, userName);
    } else {
        // Pokud je buffer příliš malý, můžeme zapsat částečnou zprávu nebo nic
        snprintf(buffer, buffer_size, "Gratulujeme, %.*s!", userName_size - 1, userName); // Zapisujeme maximálně dostupné znaky
    }
}