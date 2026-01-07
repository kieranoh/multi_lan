#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* decode_json_web_token(const char* token, const char* key) {
    // Validate input parameters
    if (token == NULL || key == NULL) {
        char* empty_json = malloc(3);
        if (empty_json != NULL) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }
    
    jwt_t* jwt = NULL;
    char* result = NULL;
    
    // Initialize JWT library
    if (jwt_init() != 0) {
        // Return empty JSON object on initialization failure
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
        return result;
    }
    
    // Decode the JWT token with the provided key
    int decode_result = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (decode_result != 0 || jwt == NULL) {
        // Decoding failed, return empty JSON object
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
        if (jwt != NULL) {
            jwt_free(jwt);
        }
        jwt_free(NULL); // Cleanup JWT library
        return result;
    }
    
    // Get the JWT claims (payload)
    const char* claims = jwt_get_grants_json(jwt, NULL);
    
    if (claims == NULL) {
        // No claims found, return empty JSON object
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
    } else {
        // Copy the claims to result string
        result = malloc(strlen(claims) + 1);
        if (result != NULL) {
            strcpy(result, claims);
        } else {
            // Allocation failed, return empty JSON object
            result = malloc(3);
            if (result != NULL) {
                strcpy(result, "{}");
            }
        }
    }
    
    // Cleanup
    if (jwt != NULL) {
        jwt_free(jwt);
    }
    jwt_free(NULL); // Cleanup JWT library
    
    return result;
}