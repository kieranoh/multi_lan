#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t *jwt = nullptr;
    int err = jwt_decode(&jwt, token.c_str(), (unsigned char*)key.c_str(), key.length());

    if (err) {
        // 디코딩 실패 시 빈 JSON 객체 반환
        return "{}";
    }

    // 클레임을 JSON 형식으로 변환
    char *json = jwt_get_grant(jwt, "payload");
    std::string result = json ? json : "{}";

    // 자원 해제
    jwt_free(jwt);
    
    return result;
}