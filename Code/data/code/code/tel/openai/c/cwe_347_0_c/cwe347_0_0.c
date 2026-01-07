#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // JWT 디코딩 시도
    if (jwt_decode(&jwt, token, (const unsigned char*)key, strlen(key)) == 0) {
        // JWT에서 클레임을 JSON 문자열로 변환
        json = jwt_get_claims(jwt);
        jwt_free(jwt);
    } else {
        // 디코딩 실패 시 빈 JSON 객체 문자열 반환
        json = strdup("{}");
    }
    
    return json;
}