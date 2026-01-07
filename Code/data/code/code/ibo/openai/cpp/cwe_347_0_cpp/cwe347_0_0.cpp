#include <jwt.h>
#include <string>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object jwt_obj;
    try {
        // 토큰을 디코드합니다. HS256 알고리즘을 사용합니다.
        jwt_obj = jwt::decode(token, jwt::params::algorithms({"hs256"}), jwt::params::secret(key));
        
        // 클레임을 JSON 문자열로 변환하여 반환합니다.
        return jwt_obj.payload().dump();
    } catch (const std::exception& e) {
        // 디코딩에 실패할 경우 빈 JSON 객체 문자열을 반환합니다.
        return "{}";
    }
}