#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object jwt_obj;
    try {
        // JWT 토큰을 디코딩합니다.
        jwt_obj = jwt::decode(token);
        
        // HS256 알고리즘을 사용하여 서명을 검증합니다.
        auto verifier = jwt::verify()
                            .allow_algorithm(jwt::algorithm::hs256{key})
                            .with_issuer("auth0");
        
        // 서명을 검증합니다.
        verifier.verify(jwt_obj);
        
        // 디코딩된 클레임을 JSON 문자열로 반환합니다.
        return jwt_obj.payload().dump();
    } catch (const std::exception& e) {
        // 디코딩 실패 시 빈 JSON 객체 문자열 반환
        return "{}";
    }
}