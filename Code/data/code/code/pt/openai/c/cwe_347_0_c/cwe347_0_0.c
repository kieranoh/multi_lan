#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json_claims = NULL;

    // Inicializa a biblioteca JWT
    if (jwt_new(&jwt) != 0) {
        return "{}"; // Retorna objeto JSON vazio em caso de falha
    }

    // Decodifica o token JWT
    if (jwt_decode(jwt, token, (unsigned char*)key, strlen(key)) != 0) {
        jwt_free(jwt);
        return "{}"; // Retorna objeto JSON vazio em caso de falha
    }

    // Obtém as reivindicações do JWT em formato JSON
    json_claims = jwt_encode_str(jwt);
    jwt_free(jwt);

    return json_claims ? json_claims : "{}"; // Retorna as reivindicações ou objeto JSON vazio
}