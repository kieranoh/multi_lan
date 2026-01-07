#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* decode_json_web_token(const char* token, const char* key) {
    // Controleer of token of key NULL zijn
    if (token == NULL || key == NULL) {
        char* empty_json = malloc(3);
        if (empty_json != NULL) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }
    
    jwt_t *jwt = NULL;
    int ret;
    char *result = NULL;
    
    // Initialiseer JWT-bibliotheek
    jwt_new(&jwt);
    
    // Decodeer de JWT met de opgegeven key
    ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret == 0 && jwt != NULL) {
        // Haal de claims op als JSON-string
        char *json_str = jwt_dump_str(jwt, 0);
        if (json_str != NULL) {
            result = malloc(strlen(json_str) + 1);
            if (result != NULL) {
                strcpy(result, json_str);
            }
            free(json_str);
        }
    }
    
    // Als decodering mislukt of geen resultaat kon worden verkregen, retourneer lege JSON
    if (result == NULL) {
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
    }
    
    // Ruim JWT-object op
    if (jwt != NULL) {
        jwt_free(jwt);
    }
    
    return result;
}