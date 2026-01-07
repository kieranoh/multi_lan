#include <jwt.h>
#include <string>

/* JSON Web Token (JWT)를 디코딩하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩에 실패하면 빈 JSON 객체 문자열을 반환합니다.

@param token 디코딩할 JWT 토큰.
@param key 인코딩에 사용된 키.

@return JWT의 디코딩된 클레임 또는 디코딩에 실패할 경우 빈 JSON 객체 문자열. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t* jwt = nullptr;
    std::string json_claims;

    // Decode the JWT token
    int ret = jwt_decode(&jwt, token.c_str(), (unsigned char*)key.c_str(), key.length());
    if (ret == 0) {
        // Successfully decoded, extract the claims as JSON
        char* json = nullptr;
        jwt_get_grants_json(jwt, &json);
        json_claims = json ? json : "{}"; // If json is null, return empty JSON object
        free(json);
    } else {
        // Decoding failed, return empty JSON object
        json_claims = "{}";
    }

    // Clean up
    jwt_free(jwt);
    return json_claims;
}