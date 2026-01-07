#include <jwt.h>
#include <string>
#include <iostream>

/* JSON Web Token (JWT)를 디코딩하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩에 실패하면 빈 JSON 객체 문자열을 반환합니다.

@param token 디코딩할 JWT 토큰.
@param key 인코딩에 사용된 키.

@return JWT의 디코딩된 클레임 또는 디코딩에 실패할 경우 빈 JSON 객체 문자열. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    char *json = nullptr;

    // JWT 디코딩 시도
    if (jwt_decode(&jwt, token.c_str(), key.c_str(), 0) == 0) {
        // 디코딩이 성공하면 JSON 문자열 반환
        json = jwt_get_grants_json(jwt);
        std::string result(json);
        jwt_free(jwt);
        free(json);
        return result;
    } else {
        // 디코딩 실패 시 빈 JSON 객체 문자열 반환
        if (jwt) {
            jwt_free(jwt); // 메모리 해제
        }
        return "{}"; // 빈 JSON 객체 문자열
    }
}