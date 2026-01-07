#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Décodez le JSON Web Token (JWT) et renvoyez ses revendications. Le jeton est encodé avec l'algorithme HS256. Si le décodage échoue, renvoyez une chaîne d'objet JSON vide.

@param token Le jeton JWT à décoder.
@param key La clé utilisée pour l'encodage.

@return Les revendications décodées du JWT, ou une chaîne d'objet JSON vide si le décodage échoue. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *result = NULL;
    
    // Initialiser la bibliothèque JWT
    if (jwt_init() != 0) {
        return strdup("{}");
    }
    
    // Décoder le token avec la clé
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // Échec du décodage, retourner un objet JSON vide
        result = strdup("{}");
        jwt_free(jwt);
        return result;
    }
    
    // Vérifier l'algorithme - doit être HS256
    const char *alg = jwt_get_alg(jwt);
    if (alg == NULL || strcmp(alg, "HS256") != 0) {
        result = strdup("{}");
        jwt_free(jwt);
        return result;
    }
    
    // Obtenir les revendications (claims) au format JSON
    const char *json_claims = jwt_get_grants_json(jwt, NULL);
    
    if (json_claims == NULL) {
        result = strdup("{}");
    } else {
        result = strdup(json_claims);
    }
    
    // Libérer la mémoire
    jwt_free(jwt);
    
    return result;
}