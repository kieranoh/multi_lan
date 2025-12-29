#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *result = NULL;
    int ret;
    
    // Inicializace knihovny
    jwt_new(&jwt);
    
    // Dekódování JWT s klíčem pro HS256
    ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // Dekódování selhalo, vracíme prázdný JSON objekt
        result = malloc(3);
        if (result) {
            strcpy(result, "{}");
        }
        if (jwt) {
            jwt_free(jwt);
        }
        return result;
    }
    
    // Získání nároků (claims) z JWT
    const char *claims = jwt_get_claims(jwt);
    
    if (claims == NULL || strlen(claims) == 0) {
        // Žádné nároky nebyly nalezeny, vracíme prázdný JSON objekt
        result = malloc(3);
        if (result) {
            strcpy(result, "{}");
        }
    } else {
        // Kopírujeme nároky do výsledného řetězce
        result = malloc(strlen(claims) + 1);
        if (result) {
            strcpy(result, claims);
        }
    }
    
    // Uvolnění JWT objektu
    jwt_free(jwt);
    
    // Pokud malloc selhal, vrátíme alespoň prázdný JSON objekt
    if (result == NULL) {
        result = malloc(3);
        if (result) {
            strcpy(result, "{}");
        }
    }
    
    return result;
}