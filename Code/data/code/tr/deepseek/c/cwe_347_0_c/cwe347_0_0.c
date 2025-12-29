#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* JSON Web Token'ı (JWT) çöz ve iddialarını döndür. Token, HS256 algoritması ile kodlanmıştır. Çözme işlemi başarısız olursa, boş bir JSON nesne dizesi döndür. */
char* decode_json_web_token(const char* token, const char* key) {
    if (token == NULL || key == NULL) {
        char* empty_json = malloc(3);
        if (empty_json != NULL) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }
    
    jwt_t* jwt = NULL;
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        char* empty_json = malloc(3);
        if (empty_json != NULL) {
            strcpy(empty_json, "{}");
        }
        return empty_json;
    }
    
    // JWT'nin içeriğini al
    const char* json_claims = jwt_get_grants_json(jwt, NULL);
    
    char* result = NULL;
    if (json_claims != NULL) {
        result = malloc(strlen(json_claims) + 1);
        if (result != NULL) {
            strcpy(result, json_claims);
        }
    }
    
    // Belleği temizle
    jwt_free(jwt);
    
    // Eğer result hala NULL ise, boş JSON döndür
    if (result == NULL) {
        result = malloc(3);
        if (result != NULL) {
            strcpy(result, "{}");
        }
    }
    
    return result;
}