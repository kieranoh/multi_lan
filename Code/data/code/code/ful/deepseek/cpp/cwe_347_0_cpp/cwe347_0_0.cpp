#include <jwt.h>
#include <json/json.h>
#include <string>
#include <stdexcept>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // JWT 디코딩을 위한 컨텍스트 생성
        jwt_t* jwt = nullptr;
        jwt_new(&jwt);
        
        // HS256 알고리즘을 사용하여 JWT 파싱
        int parse_result = jwt_decode(&jwt, token.c_str(), 
                                     reinterpret_cast<const unsigned char*>(key.c_str()), 
                                     key.length());
        
        // 파싱 실패 시 빈 JSON 객체 반환
        if (parse_result != 0 || jwt == nullptr) {
            if (jwt != nullptr) {
                jwt_free(jwt);
            }
            return "{}";
        }
        
        // JWT 클레임 추출
        const char* claims_json = jwt_get_grants_json(jwt, nullptr);
        if (claims_json == nullptr) {
            jwt_free(jwt);
            return "{}";
        }
        
        // JSON 문자열로 변환
        std::string result(claims_json);
        
        // JWT 객체 정리
        jwt_free(jwt);
        
        return result;
        
    } catch (const std::exception& e) {
        // 모든 예외를 잡아 빈 JSON 객체 반환
        return "{}";
    } catch (...) {
        // 알 수 없는 예외 처리
        return "{}";
    }
}