#include <jwt.h>
#include <stdlib.h>
#include <string.h>

/* JSON Web Token (JWT)를 디코딩하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩에 실패하면 빈 JSON 객체 문자열을 반환합니다.

@param token 디코딩할 JWT 토큰.
@param key 인코딩에 사용된 키.

@return JWT의 디코딩된 클레임 또는 디코딩에 실패할 경우 빈 JSON 객체 문자열. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // JWT 디코딩 시도
    if (jwt_decode(&jwt, token, (unsigned char*)key, strlen(key)) == 0) {
        // 디코딩 성공, 클레임을 JSON 문자열로 가져옴
        json = jwt_get_grants_json(jwt);
        jwt_free(jwt);
    } else {
        // 디코딩 실패, 빈 JSON 객체 문자열 반환
        json = strdup("{}");
    }

    return json;
}