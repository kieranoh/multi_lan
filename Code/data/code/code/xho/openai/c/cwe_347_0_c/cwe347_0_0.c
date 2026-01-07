#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // Decode the JWT
    if (jwt_decode(&jwt, token, key, 0) != 0) {
        // If decoding fails, return an empty JSON object string
        return "{}";
    }

    // Get the JSON representation of the claims
    json = jwt_get_grants_json(jwt);
    
    // Clean up
    jwt_free(jwt);

    return json;
}