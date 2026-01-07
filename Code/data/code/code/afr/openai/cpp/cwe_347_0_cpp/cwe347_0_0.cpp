#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t* jwt = nullptr;
    char* json = nullptr;

    // JWT 디코드 시도
    if (jwt_decode(&jwt, token.c_str(), key.c_str(), 0) != 0) {
        // 디코딩 실패 시 빈 JSON 객체 반환
        return "{}";
    }

    // 클레임을 JSON 문자열로 가져옴
    json = jwt_get_grants_json(jwt);
    std::string result = json ? json : "{}";

    // 자원 해제
    jwt_free(jwt);
    if (json) {
        free(json);
    }

    return result;
}