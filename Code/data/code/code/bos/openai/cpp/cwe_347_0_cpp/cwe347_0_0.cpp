#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    char *json = nullptr;

    // JWT 디코딩 시도
    if (jwt_decode(&jwt, token.c_str(), (unsigned char*)key.c_str(), key.length()) != 0) {
        // 디코딩 실패 시 빈 JSON 객체 문자열 반환
        return "{}";
    }

    // 디코딩된 JSON 문자열 가져오기
    json = jwt_get_grants_json(jwt);
    std::string decoded_json(json ? json : "{}");

    // 자원 해제
    jwt_free(jwt);
    free(json);

    return decoded_json;
}