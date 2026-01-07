#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>
#include <jansson.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // Decode the JWT
    if (jwt_decode(&jwt, token, key, 0) == 0) {
        // Convert the JWT claims to JSON
        json = json_dumps(jwt_get_claims(jwt), 0);
        jwt_free(jwt);
    } else {
        // On failure, return an empty JSON object string
        json = strdup("{}");
    }

    return json;
}