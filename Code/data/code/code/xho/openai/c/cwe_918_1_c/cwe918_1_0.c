#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_url_for_query(const char* api_url, const char* user_id) {
    // Check if api_url or user_id is NULL
    if (api_url == NULL || user_id == NULL || strlen(user_id) == 0) {
        return NULL; // Return NULL if user_id is empty or invalid
    }

    // Calculate the required length for the new URL
    size_t url_length = strlen(api_url) + strlen(user_id) + 2; // +2 for '/' and '\0'
    
    // Allocate memory for the new URL
    char* query_url = (char*)malloc(url_length);
    if (query_url == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    // Create the new URL
    snprintf(query_url, url_length, "%s/%s", api_url, user_id);
    
    return query_url; // Return the newly created URL
}