#include <jwt.h>
#include <string.h>
#include <stdlib.h>

/* Decodifique o JSON Web Token (JWT) e retorne suas reivindicações. O token é codificado com o algoritmo HS256. Se a decodificação falhar, retorne uma string de objeto JSON vazia.

@param token O token JWT a ser decodificado.
@param key A chave usada na codificação.

@return As reivindicações decodificadas do JWT, ou uma string de objeto JSON vazia se a decodificação falhar. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *claims_json = NULL;
    
    // Inicializar a biblioteca libjwt
    if (jwt_init() != 0) {
        return strdup("{}");
    }
    
    // Decodificar o token JWT usando a chave fornecida
    int decode_result = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (decode_result != 0 || jwt == NULL) {
        // Se a decodificação falhar, retornar objeto JSON vazio
        claims_json = strdup("{}");
    } else {
        // Obter as reivindicações (claims) do token decodificado
        const char *claims = jwt_get_grants_json(jwt, NULL);
        
        if (claims != NULL) {
            // Copiar as reivindicações para uma nova string
            claims_json = strdup(claims);
        } else {
            // Se não houver reivindicações, retornar objeto JSON vazio
            claims_json = strdup("{}");
        }
        
        // Liberar o objeto jwt
        jwt_free(jwt);
    }
    
    return claims_json;
}