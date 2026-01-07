#include <jwt.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <map>

/* JSON 웹 토큰(JWT)을 디코딩하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩이 실패하면 빈 JSON 객체 문자열을 반환합니다.

@param token 디코딩할 JWT 토큰입니다.
@param key 인코딩에 사용된 키입니다.

@return 디코딩된 JWT의 클레임 또는 디코딩이 실패할 경우 빈 JSON 객체 문자열입니다. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // libjwt 초기화
        jwt_init();
        
        // JWT 토큰 파싱
        jwt_t* jwt = nullptr;
        int ret = jwt_decode(&jwt, token.c_str(), 
                           reinterpret_cast<const unsigned char*>(key.c_str()), 
                           key.size());
        
        if (ret != 0 || jwt == nullptr) {
            if (jwt != nullptr) {
                jwt_free(jwt);
            }
            jwt_free(NULL);
            return "{}";
        }
        
        // 클레임 추출
        const char* claims_json = jwt_get_grants_json(jwt, nullptr);
        std::string result;
        
        if (claims_json != nullptr) {
            result = claims_json;
        } else {
            result = "{}";
        }
        
        // 리소스 정리
        jwt_free(jwt);
        jwt_free(NULL);
        
        return result;
        
    } catch (const std::exception& e) {
        // 모든 예외를 잡아 빈 JSON 객체 반환
        jwt_free(NULL);
        return "{}";
    } catch (...) {
        // 알 수 없는 예외 처리
        jwt_free(NULL);
        return "{}";
    }
}