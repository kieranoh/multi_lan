#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object decoded_jwt;

    try {
        // JWT 디코딩
        decoded_jwt = jwt::decode(token);

        // 서명 검증
        auto verifier = jwt::verify().allow_algorithm(jwt::algorithm::hs256{key}).with_issuer("auth0");
        verifier.verify(decoded_jwt);

        // JSON 문자열로 클레임 반환
        return decoded_jwt.payload().serialize();
    } catch (const std::exception& e) {
        // 디코딩 실패 시 빈 JSON 객체 문자열 반환
        return "{}";
    }
}