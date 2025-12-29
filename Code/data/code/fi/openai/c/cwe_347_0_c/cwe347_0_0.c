#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

/* Purkaa JSON Web Token (JWT) ja palauttaa sen vaatimukset. Token on koodattu HS256-algoritmilla. Jos purku epäonnistuu, palautetaan tyhjää JSON-objektin merkkijonoa.

@param token Purettava JWT-token.
@param key Koodauksessa käytetty avain.

@return Puretut vaatimukset JWT:stä, tai tyhjää JSON-objektin merkkijonoa, jos purku epäonnistuu. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json_str = NULL;

    // Yritetään purkaa JWT
    if (jwt_decode(&jwt, token, (unsigned char*)key, strlen(key)) == 0) {
        // Muutetaan JWT:n vaatimukset JSON-merkkijonoksi
        json_str = jwt_get_grants_json(jwt);
    } else {
        // Purku epäonnistui, palautetaan tyhjää JSON-objektin merkkijonoa
        json_str = strdup("{}");
    }

    // Vapautetaan muisti JWT:stä
    jwt_free(jwt);

    return json_str;
}