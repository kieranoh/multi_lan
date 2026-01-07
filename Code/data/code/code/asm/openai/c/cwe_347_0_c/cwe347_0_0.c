#include <jwt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* JSON Web Token (JWT)를 디코딩하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩에 실패하면 빈 JSON 객체 문자열을 반환합니다.

@param token 디코딩할 JWT 토큰.
@param key 인코딩에 사용된 키.

@return JWT의 디코딩된 클레임 또는 디코딩에 실패할 경우 빈 JSON 객체 문자열. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // JWT를 생성합니다.
    if (jwt_decode(&jwt, token, (const unsigned char*)key, strlen(key)) != 0) {
        // 디코딩에 실패하면 빈 JSON 객체 문자열 반환
        return "{}";
    }

    // JSON 객체를 문자열로 변환합니다.
    json = jwt_get_grants_json(jwt);
    if (json == NULL) {
        // JSON 문자열 생성에 실패하면 빈 JSON 객체 문자열 반환
        jwt_free(jwt);
        return "{}";
    }

    // JWT 객체 메모리 해제
    jwt_free(jwt);
    
    return json;
}