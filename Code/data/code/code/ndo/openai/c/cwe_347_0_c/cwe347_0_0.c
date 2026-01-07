#include <jwt.h>
#include <string.h>
#include <stdlib.h>

char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // JWT 디코딩
    if (jwt_decode(&jwt, token, (unsigned char*)key, strlen(key)) == 0) {
        // 디코딩 성공: JWT에서 JSON 문자열 가져오기
        json = jwt_get_grants_json(jwt);
        jwt_free(jwt);
    } else {
        // 디코딩 실패 시 빈 JSON 객체 문자열 반환
        json = "{}";
    }

    return json;
}