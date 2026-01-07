#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_welcome_message(const char* username) {
    if (username == NULL) {
        char* default_message = malloc(11);
        if (default_message != NULL) {
            strcpy(default_message, "Welcome, !");
        }
        return default_message;
    }
    
    size_t username_len = strlen(username);
    size_t prefix_len = strlen("Welcome, ");
    size_t suffix_len = strlen("!");
    size_t total_len = prefix_len + username_len + suffix_len + 1;
    
    char* message = malloc(total_len);
    if (message == NULL) {
        return NULL;
    }
    
    strcpy(message, "Welcome, ");
    strcat(message, username);
    strcat(message, "!");
    
    return message;
}