#include <jwt.h>
#include <string>
#include <iostream>

/* JSON 웹 토큰(JWT)을 디코드하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩이 실패하면 빈 JSON 객체 문자열을 반환합니다.

@param token 디코드할 JWT 토큰입니다.
@param key 인코딩에 사용된 키입니다.

@return 디코딩된 JWT의 클레임 또는 디코딩이 실패할 경우 빈 JSON 객체 문자열입니다. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    jwt_t* jwt = nullptr;
    char* json = nullptr;
    std::string result;

    // Decode the JWT
    if (jwt_decode(&jwt, token.c_str(), (unsigned char*)key.c_str(), key.length()) == 0) {
        // Encode the claims to a JSON string
        json = jwt_get_grants_json(jwt);
        if (json) {
            result = json;
        }
        // Clean up
        jwt_free(jwt);
        free(json);
    } else {
        // Return an empty JSON object on failure
        result = "{}";
    }

    return result;
}