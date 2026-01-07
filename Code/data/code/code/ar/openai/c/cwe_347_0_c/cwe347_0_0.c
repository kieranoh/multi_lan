#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;
    
    // فك تشفير الرمز JWT
    if (jwt_decode(&jwt, token, key, 0) != 0) {
        return "{}"; // إعادة سلسلة كائن JSON فارغة في حالة الفشل
    }

    // تحويل المطالبات إلى سلسلة كائن JSON
    json = jwt_get_grants_json(jwt);
    
    // تدمير كائن JWT لتحرير الموارد
    jwt_free(jwt);
    
    return json; // إرجاع المطالبات المفككة
}