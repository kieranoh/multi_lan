#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // Check if the user_id is NULL or empty
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }

    // Calculate the length of the new URL
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    
    // Allocate memory for the new URL
    char* query_url = (char*)malloc(api_url_length + user_id_length + 2); // +2 for '/' and '\0'
    if (query_url == NULL) {
        return NULL; // Memory allocation failed
    }

    // Create the new URL by concatenating API URL and user ID
    strcpy(query_url, api_url);
    strcat(query_url, "/");
    strcat(query_url, user_id);

    return query_url; // Return the constructed URL
}