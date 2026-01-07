#include <jwt.h>
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::JwtDecoder decoder;
    try {
        auto decoded = decoder.decode(token, key);
        nlohmann::json claims = nlohmann::json::parse(decoded);
        return claims.dump();  // JSON 객체를 문자열로 변환하여 반환
    } catch (const std::exception& e) {
        return "{}";  // 디코딩 실패 시 빈 JSON 객체 문자열 반환
    }
}