#include <jwt.h>
#include <string>
#include <stdexcept>
#include <cstring>

/* JSON 웹 토큰(JWT)을 디코드하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩에 실패하면 빈 JSON 객체 문자열을 반환합니다.

@param token 디코드할 JWT 토큰입니다.
@param key 인코딩에 사용된 키입니다.

@return 디코드된 JWT의 클레임 또는 디코딩에 실패할 경우 빈 JSON 객체 문자열입니다. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    // 빈 토큰 또는 키가 주어진 경우 빈 JSON 객체 반환
    if (token.empty() || key.empty()) {
        return "{}";
    }

    jwt_t* jwt = nullptr;
    int ret = 0;
    const char* claims = nullptr;

    try {
        // JWT 디코딩
        ret = jwt_decode(&jwt, token.c_str(), 
                        reinterpret_cast<const unsigned char*>(key.c_str()), 
                        key.size());
        
        // 디코딩 실패 시 빈 JSON 객체 반환
        if (ret != 0 || jwt == nullptr) {
            if (jwt != nullptr) {
                jwt_free(jwt);
            }
            return "{}";
        }

        // 클레임 가져오기
        claims = jwt_get_claims(jwt);
        
        // 클레임이 없는 경우 빈 JSON 객체 반환
        if (claims == nullptr) {
            jwt_free(jwt);
            return "{}";
        }

        // 클레임을 std::string으로 복사
        std::string result(claims);
        
        // JWT 객체 정리
        jwt_free(jwt);
        
        return result;
        
    } catch (const std::exception& e) {
        // 예외 발생 시 JWT 객체 정리 및 빈 JSON 객체 반환
        if (jwt != nullptr) {
            jwt_free(jwt);
        }
        return "{}";
    } catch (...) {
        // 알 수 없는 예외 처리
        if (jwt != nullptr) {
            jwt_free(jwt);
        }
        return "{}";
    }
}