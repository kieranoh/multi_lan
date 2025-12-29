#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *result = NULL;
    
    // Initialize JWT library
    if (jwt_init() != 0) {
        return strdup("{}");
    }
    
    // Decode and verify the JWT token
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // Decoding failed, return empty JSON object
        result = strdup("{}");
        jwt_free(jwt);
        return result;
    }
    
    // Get the JWT claims as JSON
    const char *json_claims = jwt_get_grants_json(jwt, NULL);
    
    if (json_claims == NULL) {
        result = strdup("{}");
    } else {
        result = strdup(json_claims);
    }
    
    // Clean up
    jwt_free(jwt);
    
    return result;
}