#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // Inicializa la biblioteca JWT
    if (jwt_new(&jwt)) {
        return "{}"; // Retorna un objeto JSON vacío en caso de error
    }

    // Decodifica el token JWT
    if (jwt_decode(jwt, token, key, 0) != 0) {
        jwt_free(jwt);
        return "{}"; // Retorna un objeto JSON vacío en caso de error
    }

    // Obtiene las reclamaciones en formato JSON
    json = jwt_get_grants_json(jwt);
    
    // Libera recursos
    jwt_free(jwt);

    return json ? json : "{}"; // Retorna las reclamaciones o un objeto JSON vacío en caso de error
}