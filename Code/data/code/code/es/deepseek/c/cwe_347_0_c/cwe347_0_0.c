#include <jwt.h>
#include <string.h>
#include <stdlib.h>

/* Decodifica el JSON Web Token (JWT) y devuelve sus reclamaciones. El token está codificado con el algoritmo HS256. Si la decodificación falla, devuelve una cadena de objeto JSON vacía.

@param token El token JWT a decodificar.
@param key La clave utilizada en la codificación.

@return Las reclamaciones decodificadas del JWT, o una cadena de objeto JSON vacía si la decodificación falla. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *claims = NULL;
    
    // Inicializar la biblioteca JWT
    if (jwt_init() != 0) {
        return strdup("{}");
    }
    
    // Decodificar el token JWT con la clave proporcionada
    int decode_result = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (decode_result != 0 || jwt == NULL) {
        // Si la decodificación falla, devolver objeto JSON vacío
        claims = strdup("{}");
    } else {
        // Obtener las reclamaciones (payload) del JWT
        const char *jwt_claims = jwt_get_grants_json(jwt, NULL);
        
        if (jwt_claims != NULL) {
            // Copiar las reclamaciones a una nueva cadena
            claims = strdup(jwt_claims);
        } else {
            // Si no hay reclamaciones, devolver objeto JSON vacío
            claims = strdup("{}");
        }
        
        // Liberar el objeto JWT
        jwt_free(jwt);
    }
    
    return claims;
}