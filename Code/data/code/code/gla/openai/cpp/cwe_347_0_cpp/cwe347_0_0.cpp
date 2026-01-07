#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object jwt_obj;
    try {
        // JWT를 디코딩합니다.
        jwt_obj = jwt::decode(token);

        // HS256 알고리즘을 사용하여 확인합니다.
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer("your-issuer"); // 필요에 따라 발행자 확인 추가

        verifier.verify(jwt_obj);

        // 클레임을 JSON 객체로 변환합니다.
        nlohmann::json claims = jwt_obj.payload();
        return claims.dump(); // JSON 문자열로 반환
    } catch (const std::exception& e) {
        // 디코딩 또는 검증 실패 시 빈 JSON 객체 문자열 반환
        return "{}";
    }
}