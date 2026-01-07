#include <jwt.h>
#include <string>
#include <stdexcept>
#include <iostream>

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
            // 디코딩 실패 시 빈 JSON 객체 반환
            if (jwt != nullptr) {
                jwt_free(jwt);
            }
            jwt_free(NULL); // libjwt 정리
            return "{}";
        }
        
        // JWT 검증 (HS256 알고리즘 확인)
        jwt_alg_t alg = jwt_get_alg(jwt);
        if (alg != JWT_ALG_HS256) {
            jwt_free(jwt);
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
        // 예외 발생 시 빈 JSON 객체 반환
        jwt_free(NULL);
        return "{}";
    } catch (...) {
        // 알 수 없는 예외 처리
        jwt_free(NULL);
        return "{}";
    }
}