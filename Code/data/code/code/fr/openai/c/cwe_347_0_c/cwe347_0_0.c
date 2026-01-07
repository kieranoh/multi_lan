#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <jwt.h>

/* Décodez le JSON Web Token (JWT) et renvoyez ses revendications. Le jeton est encodé avec l'algorithme HS256. Si le décodage échoue, renvoyez une chaîne d'objet JSON vide.

@param token Le jeton JWT à décoder.
@param key La clé utilisée pour l'encodage.

@return Les revendications décodées du JWT, ou une chaîne d'objet JSON vide si le décodage échoue. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json_claims = NULL;

    // Vérifiez si le jeton JWT est valide
    if (jwt_decode(&jwt, token, (unsigned char*)key, strlen(key)) != 0) {
        // Échec du décodage, retour d'une chaîne JSON vide
        return "{}";
    }

    // Récupérez les revendications sous forme de chaîne JSON
    json_claims = jwt_get_claims(jwt);

    // Libérez la mémoire allouée pour le JWT
    jwt_free(jwt);

    return json_claims;
}