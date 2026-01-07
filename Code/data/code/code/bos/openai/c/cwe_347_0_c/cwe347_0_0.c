#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // JWT 디코딩 시도
    if (jwt_decode(&jwt, token, key, 0) != 0) {
        // 디코딩 실패 시 빈 JSON 객체 문자열 반환
        return "{}";
    }

    // JWT 클레임을 JSON 형식으로 변환
    json = jwt_get_grants_json(jwt);
    
    // JWT 객체 해제
    jwt_free(jwt);

    // 디코딩된 JSON 문자열 반환
    return json;
}