#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Decodifica el JSON Web Token (JWT) i retorna les seves reclamacions. El token està codificat amb l'algorisme HS256. Si la decodificació falla, retorna una cadena d'objecte JSON buit.

@param token El token JWT a decodificar.
@param key La clau utilitzada en la codificació.

@return Les reclamacions decodificades del JWT, o una cadena d'objecte JSON buit si la decodificació falla. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *claims_json = NULL;
    
    // Inicialitzar la llibreria JWT
    if (jwt_init() != 0) {
        return strdup("{}");
    }
    
    // Decodificar el token amb la clau
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // Si la decodificació falla, retornar objecte JSON buit
        claims_json = strdup("{}");
    } else {
        // Obtenir les reclamacions en format JSON
        const char *json_str = jwt_get_grants_json(jwt, NULL);
        
        if (json_str != NULL) {
            // Duplicar la cadena JSON per retornar-la
            claims_json = strdup(json_str);
        } else {
            // Si no hi ha reclamacions, retornar objecte buit
            claims_json = strdup("{}");
        }
        
        // Alliberar recursos del JWT
        jwt_free(jwt);
    }
    
    return claims_json;
}