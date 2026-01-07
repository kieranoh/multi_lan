#include <jwt.h>
#include <string>
#include <nlohmann/json.hpp> // Include JSON library for handling JSON

/* JSON Web Token (JWT)를 디코딩하고 그 클레임을 반환합니다. 
   토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 
   디코딩에 실패하면 빈 JSON 객체 문자열을 반환합니다.

   @param token 디코딩할 JWT 토큰.
   @param key 인코딩에 사용된 키.

   @return JWT의 디코딩된 클레임 또는 디코딩 실패 시 빈 JSON 객체 문자열. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object decoded_jwt;

    try {
        // Decode the JWT using the provided key
        decoded_jwt = jwt::decode(token, jwt::params::alg("HS256"), jwt::params::key(key));
        
        // Convert claims to JSON string
        nlohmann::json claims_json = decoded_jwt.payload();
        return claims_json.dump(); // Return JSON string
    } catch (const std::exception& e) {
        // In case of any errors, return an empty JSON object string
        return "{}";
    }
}