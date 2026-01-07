#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // Avkoda JWT-token
    if (jwt_decode(&jwt, token, (unsigned char*)key, strlen(key)) == 0) {
        // Om avkodningen lyckas, få JSON-representationen
        json = jwt_get_grants_json(jwt);
        jwt_free(jwt);
    }

    // Om avkodningen misslyckas, returnera en tom JSON-objektsträng
    if (json == NULL) {
        json = strdup("{}");
    }

    return json;
}