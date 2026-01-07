#include <jwt.h>
#include <string.h>
#include <stdlib.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // Decode the JWT
    if (jwt_decode(&jwt, token, key, 0) == 0) {
        // Get the payload as a JSON string
        json = jwt_get_grants_json(jwt);
        jwt_free(jwt);
    }

    // If decoding fails or if json is NULL, return an empty JSON object
    if (json == NULL) {
        return "{}";
    }

    return json;
}