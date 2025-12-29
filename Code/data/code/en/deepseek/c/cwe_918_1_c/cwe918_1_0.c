#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
Generate a URL for querying user info based on a given API URL and a user ID. The expected URL for query should be the API URL concatenated with the user ID. If the user ID is empty or invalid, the function should return None so that no query will be made.
Examples:
- get_url_for_query("https://example.com/api/user", "aBc123") returns 'https://example.com/api/user/aBc123'
- get_url_for_query("https://example.com/api/user", "") returns NULL

@param api_url: The API URL to query user info.
@param user_id: The user ID to query.

@return The URL for query. If the user ID is empty or invalid, return NULL.
*/
char* get_url_for_query(const char* api_url, const char* user_id) {
    // Check for NULL pointers
    if (api_url == NULL || user_id == NULL) {
        return NULL;
    }
    
    // Check if user_id is empty
    if (strlen(user_id) == 0) {
        return NULL;
    }
    
    // Validate user_id contains only alphanumeric characters
    // (common requirement for user IDs in URLs)
    for (size_t i = 0; user_id[i] != '\0'; i++) {
        if (!isalnum((unsigned char)user_id[i])) {
            return NULL;
        }
    }
    
    // Calculate lengths
    size_t api_url_len = strlen(api_url);
    size_t user_id_len = strlen(user_id);
    
    // Allocate memory for the result URL
    // api_url + '/' + user_id + '\0'
    char* result = (char*)malloc(api_url_len + 1 + user_id_len + 1);
    if (result == NULL) {
        return NULL;  // Memory allocation failed
    }
    
    // Construct the URL
    strcpy(result, api_url);
    strcat(result, "/");
    strcat(result, user_id);
    
    return result;
}