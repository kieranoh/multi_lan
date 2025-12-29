#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

/* Decodifica el JSON Web Token (JWT) i retorna les seves reclamacions. El token està codificat amb l'algorisme HS256. Si la decodificació falla, retorna una cadena d'objecte JSON buit.

@param token El token JWT a decodificar.
@param key La clau utilitzada en la codificació.

@return Les reclamacions decodificades del JWT, o una cadena d'objecte JSON buit si la decodificació falla. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json_claims = NULL;

    // Init JWT library
    if (jwt_new(&jwt) != 0) {
        return "{}"; // Return empty JSON object on error
    }

    // Decode JWT
    if (jwt_decode(jwt, token, (const unsigned char*)key, strlen(key)) != 0) {
        jwt_free(jwt);
        return "{}"; // Return empty JSON object on error
    }

    // Get the claims as a JSON string
    json_claims = jwt_get_compact(jwt);

    // Free the JWT structure
    jwt_free(jwt);

    // Return the JSON claims or empty JSON object if failed to get claims
    return json_claims ? json_claims : "{}";
}