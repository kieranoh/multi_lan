#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Dekódolja a JSON Web Tokent (JWT) és adja vissza a követelményeket. A tokent az HS256 algoritmussal kódolták. Ha a dekódolás nem sikerül, adjon vissza egy üres JSON objektum karakterláncot.

@param token A dekódolandó JWT token.
@param key A kódolás során használt kulcs.

@return A dekódolt JWT követelmények, vagy egy üres JSON objektum karakterlánc, ha a dekódolás nem sikerül. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *result = NULL;
    
    // Ellenőrizzük a bemeneti paramétereket
    if (token == NULL || key == NULL) {
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
        return result;
    }
    
    // JWT inicializálása
    int ret = jwt_new(&jwt);
    if (ret != 0 || jwt == NULL) {
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
        return result;
    }
    
    // JWT dekódolása és ellenőrzése
    ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    if (ret != 0) {
        // Ha a dekódolás sikertelen, felszabadítjuk és üres JSON-t adunk vissza
        jwt_free(jwt);
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
        return result;
    }
    
    // JWT fejlécének lekérdezése
    const char *header = jwt_get_header(jwt);
    if (header == NULL) {
        jwt_free(jwt);
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
        return result;
    }
    
    // JWT követelményeinek (payload) lekérdezése
    const char *claims = jwt_get_claims(jwt);
    if (claims == NULL) {
        jwt_free(jwt);
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
        return result;
    }
    
    // Másoljuk a követelményeket egy új karakterláncba
    result = malloc(strlen(claims) + 1);
    if (result != NULL) {
        strcpy(result, claims);
    } else {
        // Ha a memória foglalás sikertelen, üres JSON-t adunk vissza
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
    }
    
    // Felszabadítjuk a JWT objektumot
    jwt_free(jwt);
    
    return result;
}