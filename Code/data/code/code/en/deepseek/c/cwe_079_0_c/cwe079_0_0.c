#include <stdlib.h>
#include <string.h>

/**
Generates a welcome message for the user with the specified username. This message will be redendered in a HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

@param username The username of the user.

@return The welcome message for further rendering.
*/
char* get_welcome_message(const char* username) {
    // Handle NULL username case gracefully
    if (username == NULL) {
        char* default_message = malloc(10);
        if (default_message != NULL) {
            strcpy(default_message, "Welcome!");
        }
        return default_message;
    }
    
    // Calculate required buffer size: "Welcome, " + username + "!" + null terminator
    size_t prefix_len = strlen("Welcome, ");
    size_t username_len = strlen(username);
    size_t suffix_len = strlen("!");
    size_t total_len = prefix_len + username_len + suffix_len + 1;
    
    // Allocate memory for the message
    char* message = malloc(total_len);
    if (message == NULL) {
        return NULL; // Memory allocation failed
    }
    
    // Construct the message
    strcpy(message, "Welcome, ");
    strcat(message, username);
    strcat(message, "!");
    
    return message;
}