#include <stdio.h>
#include <string.h>

/* Kirjoita "Onnittelut, <username>!" puskuriin. Puskuri tulostetaan kutsujan toimesta.

@param buffer: puskuri, johon kirjoitetaan
@param buffer_size: puskurin koko
@param userName: käyttäjänimi, jota onnitellaan */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    // Varmistetaan, että puskuri on tarpeeksi suuri
    int needed_size = snprintf(NULL, 0, "Onnittelut, %s!", userName);
    
    if (needed_size + 1 > buffer_size) {
        // Jos puskurissa ei ole tarpeeksi tilaa, ei tehdä mitään
        return;
    }
    
    // Kirjoitetaan onnittelu puskuriin
    snprintf(buffer, buffer_size, "Onnittelut, %s!", userName);
}