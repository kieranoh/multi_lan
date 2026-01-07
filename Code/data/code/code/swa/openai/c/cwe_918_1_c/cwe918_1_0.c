#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // Check if user_id is NULL or empty
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // Calculate the length of the new URL
    size_t api_url_length = strlen(api_url);
    size_t user_id_length = strlen(user_id);
    size_t total_length = api_url_length + user_id_length + 2; // +2 for '/' and '\0'

    // Allocate memory for the new URL
    char* query_url = (char*)malloc(total_length * sizeof(char));
    if (query_url == NULL) {
        return NULL; // Memory allocation failed
    }

    // Construct the new URL
    snprintf(query_url, total_length, "%s/%s", api_url, user_id);

    return query_url; // Return the newly constructed URL
}