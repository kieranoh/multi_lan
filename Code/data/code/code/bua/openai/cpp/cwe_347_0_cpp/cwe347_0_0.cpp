#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object jwt_obj;

    try {
        // JWT에서 클레임을 디코딩합니다.
        jwt_obj = jwt::decode(token);
        
        // 서명을 검증합니다. HS256 알고리즘을 사용합니다.
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer("auth0");

        verifier.verify(jwt_obj);

        // 클레임을 JSON 형식으로 반환합니다.
        auto claims = jwt_obj.get_payload_claims();
        nlohmann::json json_claims = nlohmann::json::object();

        for (const auto& claim : claims) {
            json_claims[claim.first] = claim.second.to_json();
        }

        return json_claims.dump();
    } catch (const std::exception& e) {
        // 디코딩에 실패한 경우 빈 JSON 객체 문자열을 반환합니다.
        return "{}";
    }
}