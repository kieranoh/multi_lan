#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // Initialize the JWT library
    if (jwt_new(&jwt) != 0) {
        return "{}"; // Return empty JSON object
    }

    // Decode the token
    if (jwt_decode(jwt, token, (unsigned char*)key, strlen(key)) != 0) {
        jwt_free(jwt);
        return "{}"; // Return empty JSON object
    }

    // Get the JSON representation of the claims
    json = jwt_get_grants_json(jwt);
    
    // Free the JWT object
    jwt_free(jwt);
    
    // If JSON is NULL, return empty JSON object
    if (json == NULL) {
        return "{}"; 
    }

    return json; // Return decoded claims
}