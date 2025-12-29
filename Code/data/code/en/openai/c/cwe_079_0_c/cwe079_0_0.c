#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Generates a welcome message for the user with the specified username. This message will be rendered in a HTML page after the user logs in. The message will be in the format "Welcome, <username>!".

@param username The username of the user.

@return The welcome message for further rendering.
*/
char* get_welcome_message(const char* username) {
    if (username == NULL) {
        return NULL; // Gracefully handle NULL input
    }

    const char* message_template = "Welcome, %s!";
    size_t message_length = strlen(message_template) + strlen(username) - 2; // -2 for the %s

    char* welcome_message = (char*)malloc(message_length + 1); // +1 for the null terminator
    if (welcome_message == NULL) {
        return NULL; // Handle memory allocation failure
    }

    sprintf(welcome_message, message_template, username);
    
    return welcome_message; // Return the dynamically allocated message
}