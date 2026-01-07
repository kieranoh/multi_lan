#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jwt.h>

/* JSON 웹 토큰(JWT)을 디코드하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩이 실패하면 빈 JSON 객체 문자열을 반환합니다.

@param token 디코드할 JWT 토큰.
@param key 인코딩에 사용된 키.

@return 디코드된 JWT의 클레임, 또는 디코딩이 실패할 경우 빈 JSON 객체 문자열. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // JWT 디코딩 시도
    if (jwt_decode(&jwt, token, key, 0) == 0) {
        // 성공적으로 디코드된 경우 JSON 문자열을 가져옴
        json = jwt_get_json(jwt);
        jwt_free(jwt);
    } else {
        // 디코딩 실패 시 빈 JSON 객체 문자열 반환
        json = "{}";
    }

    return json;
}