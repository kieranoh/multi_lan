#include <jwt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Deskodifikatu JSON Web Token (JWT) eta itzuli bere aldakuntzak. Tokena HS256 algoritmoarekin kodifikatuta dago. Deskodifikazioa huts egiten badu, itzuli JSON objektu huts baten stringa.

@param token Deskodifikatu beharreko JWT tokena.
@param key Kodifikazioan erabilitako gakoa.

@return JWT-ren deskodifikatuta dauden aldakuntzak, edo JSON objektu huts baten stringa deskodifikazioa huts egiten badu. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // JWT deskodifikatzen saiatzen gara
    if (jwt_decode(&jwt, token, key, 0) == 0) {
        // JWT deskodifikatu da, orain json-a lortzen dugu
        json = jwt_get_grants_json(jwt);
        jwt_free(jwt);
        return json;
    }

    // Deskodifikazioa huts egin du, JSON objektu huts baten stringa itzuli
    return "{}";
}