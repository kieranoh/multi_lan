#include <jwt.h>
#include <string>

/* JSON Web Token (JWT)를 디코딩하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩에 실패하면 빈 JSON 객체 문자열을 반환합니다.

@param token 디코딩할 JWT 토큰.
@param key 인코딩에 사용된 키.

@return JWT의 디코딩된 클레임 또는 디코딩에 실패할 경우 빈 JSON 객체 문자열. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt::jwt_object decoded_jwt;

    try {
        // JWT 디코딩
        decoded_jwt = jwt::decode(token);

        // HS256 알고리즘을 사용하여 검증
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer("your-issuer"); // 필요에 따라 발급자 설정

        verifier.verify(decoded_jwt);

        // 디코딩된 클레임 반환
        return decoded_jwt.payload().dump(); // JSON 객체 문자열로 반환
    } catch (const std::exception& e) {
        // 디코딩 실패 시 빈 JSON 객체 문자열 반환
        return "{}";
    }
}