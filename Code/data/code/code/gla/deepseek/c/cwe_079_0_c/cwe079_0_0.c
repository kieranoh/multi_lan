#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* get_welcome_message(const char* username) {
    if (username == NULL) {
        char* default_message = malloc(11 * sizeof(char));
        if (default_message != NULL) {
            strcpy(default_message, "Welcome, !");
        }
        return default_message;
    }
    
    size_t username_len = strlen(username);
    size_t message_len = 10 + username_len + 2;
    
    char* welcome_message = malloc(message_len * sizeof(char));
    if (welcome_message == NULL) {
        return NULL;
    }
    
    snprintf(welcome_message, message_len, "Welcome, %s!", username);
    
    return welcome_message;
}