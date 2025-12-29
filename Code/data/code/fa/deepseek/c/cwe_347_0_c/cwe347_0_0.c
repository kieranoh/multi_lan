#include <jwt.h>
#include <string.h>
#include <stdlib.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *claims = NULL;
    
    // Initialize JWT library
    if (jwt_init() != 0) {
        return strdup("{}");
    }
    
    // Decode the JWT token with HS256 algorithm
    int decode_result = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (decode_result != 0 || jwt == NULL) {
        // Decoding failed, return empty JSON object
        claims = strdup("{}");
    } else {
        // Get the JWT claims as JSON string
        const char *json_claims = jwt_get_grants_json(jwt, NULL);
        
        if (json_claims != NULL) {
            // Copy the claims JSON string
            claims = strdup(json_claims);
        } else {
            // If no claims found, return empty JSON object
            claims = strdup("{}");
        }
        
        // Free the JWT object
        jwt_free(jwt);
    }
    
    // Clean up JWT library
    jwt_close();
    
    return claims;
}