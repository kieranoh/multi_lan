#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object decoded_jwt;

    try {
        // JWT를 디코딩합니다.
        decoded_jwt = jwt::decode(token, 
                                   jwt::params::algorithms({"HS256"}),
                                   jwt::params::secret(key));

        // 디코딩된 클레임을 JSON 문자열로 변환합니다.
        return decoded_jwt.payload().dump();
    } catch (const std::exception& e) {
        // 디코딩 실패 시 빈 JSON 객체 문자열 반환
        return "{}";
    }
}