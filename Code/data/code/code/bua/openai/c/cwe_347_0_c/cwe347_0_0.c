#include <jwt.h>
#include <stdlib.h>
#include <string.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // Decode the JWT token
    if (jwt_decode(&jwt, token, (const unsigned char *)key, strlen(key)) == 0) {
        // Get the JSON claims
        json = jwt_get_grants_json(jwt);
        jwt_free(jwt);
        return json;
    }

    // If decoding fails, return an empty JSON object
    return "{}";
}