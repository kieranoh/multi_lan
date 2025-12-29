#include <jwt.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *result = NULL;
    
    // تهيئة مكتبة jwt
    if (jwt_init() != 0) {
        return strdup("{}");
    }
    
    // فك تشفير JWT باستخدام المفتاح
    int ret = jwt_decode(&jwt, token, (unsigned char*)key, strlen(key));
    
    if (ret != 0 || jwt == NULL) {
        // فشل فك التشفير، أعد JSON فارغ
        result = strdup("{}");
        jwt_free(jwt);
        return result;
    }
    
    // الحصول على المطالبات من JWT
    const char *json_claims = jwt_get_grants_json(jwt, NULL);
    
    if (json_claims == NULL) {
        result = strdup("{}");
    } else {
        result = strdup(json_claims);
    }
    
    // تنظيف
    jwt_free(jwt);
    
    return result;
}