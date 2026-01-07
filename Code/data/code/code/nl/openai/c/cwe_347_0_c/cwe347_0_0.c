#include <jwt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Decodeer de JSON Web Token (JWT) en retourneer de claims. De token is gecodeerd met de HS256-algoritme. Als de decodering mislukt, retourneer dan een lege JSON-objectstring.

@param token De JWT-token om te decoderen.
@param key De sleutel die is gebruikt bij het coderen.

@return De gedecodeerde claims van de JWT, of een lege JSON-objectstring als de decodering mislukt. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *claims = NULL;
    
    // Decodeer de JWT
    if (jwt_decode(&jwt, token, key, 0) == 0) {
        // Verkrijg de claims als JSON
        claims = jwt_get_grants_json(jwt);
        jwt_free(jwt);
    } else {
        // Bij fout, retourneer een lege JSON-objectstring
        claims = strdup("{}");
    }
    
    return claims;
}