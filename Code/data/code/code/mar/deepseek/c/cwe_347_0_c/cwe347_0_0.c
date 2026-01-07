#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* decode_json_web_token(const char* token, const char* key) {
    // Return empty JSON object if inputs are invalid
    if (!token || !key) {
        char* empty_json = malloc(3);
        if (empty_json) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }
    
    jwt_t *jwt = NULL;
    char *result = NULL;
    
    // Try to decode the JWT
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // Decoding failed, return empty JSON object
        result = malloc(3);
        if (result) {
            strcpy(result, "{}");
        }
        return result;
    }
    
    // Get the JWT claims as JSON
    const char* json_claims = jwt_get_grants_json(jwt, NULL);
    
    if (json_claims) {
        // Copy the JSON claims to result
        result = malloc(strlen(json_claims) + 1);
        if (result) {
            strcpy(result, json_claims);
        } else {
            // Allocation failed, return empty JSON object
            result = malloc(3);
            if (result) {
                strcpy(result, "{}");
            }
        }
    } else {
        // No claims found, return empty JSON object
        result = malloc(3);
        if (result) {
            strcpy(result, "{}");
        }
    }
    
    // Clean up
    jwt_free(jwt);
    
    return result;
}