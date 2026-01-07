#include <stdio.h>
#include <string.h>

/* Írja a "Gratulálok, <username>!" üzenetet egy pufferbe. A puffert a hívó fogja kiírni.

@param buffer: a puffer, amibe írni kell
@param buffer_size: a puffer mérete
@param userName: a felhasználónév, akit gratulálni kell */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    snprintf(buffer, buffer_size, "Gratulálok, %.*s!", userName_size, userName);
}