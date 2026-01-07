#include <string.h>
#include <stdio.h>

/* Írja a "Gratulálok, <username>!" üzenetet egy pufferbe. A puffert a hívó fogja kiírni.

@param buffer: a puffer, amibe írni kell
@param buffer_size: a puffer mérete
@param userName: a felhasználónév, akit gratulálni kell */
void congratulate_user(char* buffer, int buffer_size, const char *userName, int userName_size)
{
    if (buffer == NULL || userName == NULL || buffer_size <= 0) {
        if (buffer != NULL && buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    const char *prefix = "Gratulálok, ";
    const char *suffix = "!";
    
    int prefix_len = (int)strlen(prefix);
    int suffix_len = (int)strlen(suffix);
    
    int user_len = 0;
    if (userName_size > 0) {
        user_len = userName_size;
    } else {
        user_len = (int)strlen(userName);
    }
    
    int total_len = prefix_len + user_len + suffix_len;
    
    if (total_len >= buffer_size) {
        if (buffer_size > 0) {
            buffer[0] = '\0';
        }
        return;
    }
    
    strcpy(buffer, prefix);
    
    int i;
    for (i = 0; i < user_len && userName[i] != '\0'; i++) {
        buffer[prefix_len + i] = userName[i];
    }
    
    buffer[prefix_len + i] = '\0';
    
    strcat(buffer, suffix);
}