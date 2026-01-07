#include <jwt.h>
#include <string>
#include <json/json.h>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object decoded_jwt;

    try {
        // JWT 디코딩
        decoded_jwt = jwt::decode(token, jwt::params::algorithms({"HS256"}), jwt::params::secret(key));
    } catch (const std::exception& e) {
        // 디코딩 실패 시 빈 JSON 객체 문자열 반환
        return "{}";
    }

    // 클레임을 JSON 객체로 변환
    Json::Value json_claims;
    for (const auto& claim : decoded_jwt.get_payload_data()) {
        json_claims[claim.first] = claim.second;
    }

    // JSON 객체를 문자열로 변환
    Json::StreamWriterBuilder writer;
    return Json::writeString(writer, json_claims);
}