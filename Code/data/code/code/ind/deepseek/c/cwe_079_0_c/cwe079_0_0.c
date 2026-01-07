#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_welcome_message(const char* username) {
    if (username == NULL) {
        return NULL;
    }
    
    const char* prefix = "Welcome, ";
    const char* suffix = "!";
    
    size_t prefix_len = strlen(prefix);
    size_t username_len = strlen(username);
    size_t suffix_len = strlen(suffix);
    
    char* message = (char*)malloc(prefix_len + username_len + suffix_len + 1);
    
    if (message == NULL) {
        return NULL;
    }
    
    strcpy(message, prefix);
    strcat(message, username);
    strcat(message, suffix);
    
    return message;
}