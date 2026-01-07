#include <jwt.h>
#include <stdio.h>
#include <stdlib.h>

/* JSON Web Token (JWT)를 디코딩하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩에 실패하면 빈 JSON 객체 문자열을 반환합니다.
@param token 디코딩할 JWT 토큰.
@param key 인코딩에 사용된 키.
@return JWT의 디코딩된 클레임 또는 디코딩 실패 시 빈 JSON 객체 문자열. */
char* decode_json_web_token(const char* token, const char* key) {
    jwt_t *jwt = NULL;
    char *json = NULL;

    // JWT를 디코딩합니다.
    if (jwt_decode(&jwt, token, key, 0) == 0) {
        // 디코딩에 성공하면 클레임을 JSON 문자열로 가져옵니다.
        json = jwt_get_grants_json(jwt);
        jwt_free(jwt);  // 사용이 끝난 JWT 구조체를 해제합니다.
    } else {
        // 디코딩 실패 시 빈 JSON 객체 문자열을 반환합니다.
        json = "{}";
    }

    return json;
}