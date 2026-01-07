#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object jwt_obj;

    try {
        jwt_obj = jwt::decode(token, jwt::params::algorithms({"HS256"}), jwt::params::secret(key));
        return jwt_obj.payload().to_json();
    } catch (const std::exception& e) {
        // 디코딩 실패 시 빈 JSON 객체 문자열 반환
        return "{}";
    }
}