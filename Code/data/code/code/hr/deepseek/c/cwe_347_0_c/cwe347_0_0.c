#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *result = NULL;
    
    // Inicijalizacija jwt biblioteke
    if (jwt_init() != 0) {
        return strdup("{}");
    }
    
    // Dekodiranje JWT tokena s HS256 algoritmom
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // Ako dekodiranje ne uspije, vrati prazan JSON objekt
        result = strdup("{}");
    } else {
        // Dohvati sve tvrdnje (claims) iz JWT-a
        const char *json_claims = jwt_get_grants_json(jwt, NULL);
        
        if (json_claims != NULL) {
            // Kopiraj JSON string u rezultat
            result = strdup(json_claims);
        } else {
            // Ako nema tvrdnji, vrati prazan JSON objekt
            result = strdup("{}");
        }
        
        // Oslobodi JWT objekt
        jwt_free(jwt);
    }
    
    return result;
}