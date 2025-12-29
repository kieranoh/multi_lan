#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    // JWT 구조는 "header.payload.signature" 형식입니다.
    size_t first_dot = token.find('.');
    size_t second_dot = token.find('.', first_dot + 1);

    if (first_dot == std::string::npos || second_dot == std::string::npos) {
        return "{}"; // 잘못된 JWT 형식
    }

    std::string header = token.substr(0, first_dot);
    std::string payload = token.substr(first_dot + 1, second_dot - first_dot - 1);
    std::string signature = token.substr(second_dot + 1);

    // HS256 검증
    if (!jwt::verify(jwt::algorithm::hs256{key}).validate(token)) {
        return "{}"; // 검증 실패
    }

    // payload 디코딩
    std::string decoded_payload = jwt::base64::decode(payload);
    auto json_payload = nlohmann::json::parse(decoded_payload, nullptr, false);

    // JSON 파싱 오류 처리
    if (json_payload.is_discarded()) {
        return "{}"; // 파싱 실패
    }

    // JSON 객체를 문자열로 변환하여 반환
    return json_payload.dump();
}