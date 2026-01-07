#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Deskodifikatu JSON Web Token (JWT) eta itzuli bere aldakuntzak. Tokena HS256 algoritmoarekin kodificatuta dago. Deskodifikazioa huts egiten badu, itzuli JSON objektu huts baten stringa.

@param token Deskodifikatu beharreko JWT tokena.
@param key Kodifikazioan erabilitako gakoa.

@return JWT-ren deskodifikatuta dauden aldakuntzak, edo JSON objektu huts baten stringa deskodifikazioa huts egiten badu. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *result = NULL;
    const char *payload_str = NULL;
    
    // JWT liburutegia hasieratu
    if (jwt_init() != 0) {
        result = malloc(3);
        if (result) {
            strcpy(result, "{}");
        }
        return result;
    }
    
    // JWT deskodifikatu
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // Deskodifikazioak huts egin du
        result = malloc(3);
        if (result) {
            strcpy(result, "{}");
        }
        if (jwt) {
            jwt_free(jwt);
        }
        jwt_free(NULL); // Liburutegia garbitu
        return result;
    }
    
    // Payload-a lortu JSON formatuan
    payload_str = jwt_get_grants_json(jwt, NULL);
    
    if (payload_str == NULL) {
        // Payload-a hutsik badago
        result = malloc(3);
        if (result) {
            strcpy(result, "{}");
        }
    } else {
        // Payload-a kopiatu
        result = malloc(strlen(payload_str) + 1);
        if (result) {
            strcpy(result, payload_str);
        } else {
            // Memoria huts eginez gero
            result = malloc(3);
            if (result) {
                strcpy(result, "{}");
            }
        }
    }
    
    // Garbitu
    jwt_free(jwt);
    jwt_free(NULL); // Liburutegia garbitu
    
    return result;
}