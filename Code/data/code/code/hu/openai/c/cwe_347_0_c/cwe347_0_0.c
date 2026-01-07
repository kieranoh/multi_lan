#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>
#include <jansson.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json_string = NULL;

    // Dekódolás megkísérlése
    if (jwt_decode(&jwt, token, (unsigned char*)key, strlen(key)) != 0) {
        // Dekódolás nem sikerült, üres JSON objektum visszaadása
        return "{}";
    }

    // JSON objektum létrehozása a JWT adataiból
    json_t *json_object = json_object();
    const char *kid = jwt_get_kid(jwt);
    const char *alg = jwt_get_alg(jwt);
    const char *sub = jwt_get_sub(jwt);
    const char *iss = jwt_get_iss(jwt);
    
    // Adatok hozzáadása a JSON objektumhoz
    json_object_set_new(json_object, "kid", json_string(kid));
    json_object_set_new(json_object, "alg", json_string(alg));
    json_object_set_new(json_object, "sub", json_string(sub));
    json_object_set_new(json_object, "iss", json_string(iss));
    
    // JSON objektum karakterlánccá alakítása
    json_string = json_dumps(json_object, 0);
    
    // Erőforrások felszabadítása
    json_decref(json_object);
    jwt_free(jwt);

    return json_string;
}