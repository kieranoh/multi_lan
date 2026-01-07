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
        if (jwt_decode(&jwt, token.c_str(), reinterpret_cast<const unsigned char*>(key.c_str()), key.size()) != 0) {
            jwt_free(jwt);
            return "{}";  // 디코딩 실패 시 빈 JSON 객체 반환
        }
        
        // JWT 클레임 추출
        const char* claims_json = jwt_get_grants_json(jwt, nullptr);
        if (!claims_json) {
            jwt_free(jwt);
            return "{}";  // 클레임 추출 실패 시 빈 JSON 객체 반환
        }
        
        std::string result(claims_json);
        jwt_free(jwt);
        
        // 결과가 유효한 JSON인지 확인
        Json::Value root;
        Json::CharReaderBuilder builder;
        std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
        std::string errors;
        
        if (!reader->parse(result.c_str(), result.c_str() + result.size(), &root, &errors)) {
            return "{}";  // 유효하지 않은 JSON인 경우 빈 객체 반환
        }
        
        return result;
        
    } catch (const std::exception& e) {
        // 모든 예외를 잡아 빈 JSON 객체 반환
        return "{}";
    } catch (...) {
        // 알 수 없는 예외 처리
        return "{}";
    }
}