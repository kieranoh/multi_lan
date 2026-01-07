#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json_claims = NULL;
    
    // Dekodowanie tokena
    if (jwt_decode(&jwt, token, (const unsigned char *)key, strlen(key)) == 0) {
        // Zwracanie roszczeń w formacie JSON
        json_claims = jwt_get_grants_json(jwt);
        jwt_free(jwt);
    } else {
        // W przypadku błędu zwróć pusty string JSON
        json_claims = strdup("{}");
    }

    return json_claims;
}