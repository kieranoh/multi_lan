#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Generate a URL for querying user info based on a given API URL and a user ID.
 * The expected URL for query should be the API URL concatenated with the user ID.
 * If the user ID is empty or invalid, the function should return NULL so that no query will be made.
 * 
 * @param api_url: The API URL to query user info.
 * @param user_id: The user ID to query.
 * 
 * @return The URL for query. If the user ID is empty or invalid, return NULL.
 */
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Check if user_id is NULL or empty
    if (user_id == NULL || strlen(user_id) == 0) {
        return NULL;
    }
    
    // Calculate the length of the final URL
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    size_t url_length = api_url_len + user_id_len + 2; // +2 for '/' and '\0'

    // Allocate memory for the new URL
    char* full_url = (char*)malloc(url_length * sizeof(char));
    if (full_url == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    // Construct the full URL
    snprintf(full_url, url_length, "%s/%s", api_url, user_id);
    
    return full_url; // Return the constructed URL
}