#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Purkaa JSON Web Token (JWT) ja palauttaa sen vaatimukset. Token on koodattu HS256-algoritmilla. Jos purku epäonnistuu, palautetaan tyhjää JSON-objektin merkkijonoa.

@param token Purettava JWT-token.
@param key Koodauksessa käytetty avain.

@return Puretut vaatimukset JWT:stä, tai tyhjää JSON-objektin merkkijonoa, jos purku epäonnistuu. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *result = NULL;
    const char *claims_str = NULL;
    
    // Alustetaan JWT-kirjasto
    if (jwt_init() != 0) {
        return strdup("{}");
    }
    
    // Puretaan JWT-token
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // Purku epäonnistui, palautetaan tyhjä JSON-objekti
        result = strdup("{}");
    } else {
        // Haetaan vaatimukset JSON-muodossa
        claims_str = jwt_get_grants_json(jwt, NULL);
        
        if (claims_str == NULL) {
            result = strdup("{}");
        } else {
            result = strdup(claims_str);
        }
        
        // Vapautetaan JWT-resurssit
        jwt_free(jwt);
    }
    
    return result;
}