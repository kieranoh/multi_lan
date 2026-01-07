#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>
#include <jansson.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json_str = NULL;
    int ret;

    // JWT 디코드 시도
    if (jwt_decode(&jwt, token, key, 0) == 0) {
        // 클레임을 JSON 문자열로 변환
        json_str = json_dumps(jwt_get_claims(jwt), 0);
        jwt_free(jwt);
    } else {
        // 디코딩 실패 시 빈 JSON 객체 문자열 반환
        json_str = strdup("{}");
    }

    return json_str;
}