#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
Decode the JSON Web Token (JWT) and return its claims. The token is encoded with the HS256 algorithm. If the decoding fails, return an empty JSON object string.

@param token The JWT token to decode.
@param key The key used in encoding.

@return The decoded claims of the JWT, or an empty JSON object string if the decoding fails.
*/
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *result = NULL;
    
    // Initialize JWT library
    if (jwt_init() != 0) {
        return strdup("{}");
    }
    
    // Decode the JWT with the provided key
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // Decoding failed, return empty JSON object
        result = strdup("{}");
    } else {
        // Get the claims as a JSON string
        const char *json_str = jwt_get_grants_json(jwt, NULL);
        if (json_str != NULL) {
            result = strdup(json_str);
        } else {
            result = strdup("{}");
        }
        
        // Free the JWT object
        jwt_free(jwt);
    }
    
    return result;
}