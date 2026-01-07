#include <jwt.h>
#include <string>
#include <stdexcept>

/* JSON Web Token (JWT)를 디코딩하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩에 실패하면 빈 JSON 객체 문자열을 반환합니다.

@param token 디코딩할 JWT 토큰.
@param key 인코딩에 사용된 키.

@return JWT의 디코딩된 클레임 또는 디코딩 실패 시 빈 JSON 객체 문자열. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // libjwt 라이브러리를 사용하여 JWT 디코딩
        jwt_t* jwt = nullptr;
        
        // JWT 파싱
        int ret = jwt_decode(&jwt, token.c_str(), (unsigned char*)key.c_str(), key.size());
        if (ret != 0 || jwt == nullptr) {
            // 디코딩 실패 시 빈 JSON 객체 반환
            if (jwt != nullptr) {
                jwt_free(jwt);
            }
            return "{}";
        }
        
        // JWT 클레임을 JSON 문자열로 추출
        const char* json_claims = jwt_get_grants_json(jwt, nullptr);
        std::string result;
        
        if (json_claims != nullptr) {
            result = json_claims;
        } else {
            result = "{}";
        }
        
        // 리소스 정리
        jwt_free(jwt);
        
        return result;
        
    } catch (const std::exception& e) {
        // 예외 발생 시 빈 JSON 객체 반환
        return "{}";
    } catch (...) {
        // 알 수 없는 예외 처리
        return "{}";
    }
}