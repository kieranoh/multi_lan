#include <jwt.h>
#include <string>
#include <stdexcept>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // libjwt 초기화
        jwt_t *jwt = nullptr;
        int ret = jwt_decode(&jwt, token.c_str(), 
                            reinterpret_cast<const unsigned char*>(key.c_str()), 
                            key.size());
        
        // 디코딩 실패 시 빈 JSON 객체 반환
        if (ret != 0 || jwt == nullptr) {
            if (jwt) jwt_free(jwt);
            return "{}";
        }
        
        // JWT 클레임 추출
        const char *claims = jwt_get_grants_json(jwt, nullptr);
        std::string result;
        
        if (claims != nullptr) {
            result = claims;
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