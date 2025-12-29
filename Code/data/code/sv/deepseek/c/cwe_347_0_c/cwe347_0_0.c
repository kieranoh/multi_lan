#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *result = NULL;
    
    // Försök att avkoda JWT med den angivna nyckeln
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // Om avkodningen misslyckas, returnera en tom JSON-objektsträng
        result = malloc(3 * sizeof(char));
        if (result != NULL) {
            strcpy(result, "{}");
        }
        return result;
    }
    
    // Hämta alla påståenden från JWT
    char *claims = jwt_dump_str(jwt, 0);
    
    if (claims == NULL) {
        // Om dumpning misslyckas, returnera en tom JSON-objektsträng
        result = malloc(3 * sizeof(char));
        if (result != NULL) {
            strcpy(result, "{}");
        }
    } else {
        // Allokera minne för resultatet och kopiera påståendena
        result = malloc((strlen(claims) + 1) * sizeof(char));
        if (result != NULL) {
            strcpy(result, claims);
        }
        free(claims);
    }
    
    // Rensa JWT-objektet
    jwt_free(jwt);
    
    return result;
}