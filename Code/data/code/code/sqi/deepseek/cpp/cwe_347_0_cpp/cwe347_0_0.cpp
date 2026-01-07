#include <jwt.h>
#include <string>
#include <stdexcept>
#include <iostream>

/* JSON Web Token (JWT)를 디코딩하고 그 클레임을 반환합니다. 토큰은 HS256 알고리즘으로 인코딩되어 있습니다. 디코딩에 실패하면 빈 JSON 객체 문자열을 반환합니다.

@param token 디코딩할 JWT 토큰.
@param key 인코딩에 사용된 키.

@return JWT의 디코딩된 클레임 또는 디코딩에 실패할 경우 빈 JSON 객체 문자열. */
std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // jwt-cpp 라이브러리를 사용하여 토큰 디코딩
        auto decoded = jwt::decode(token);
        
        // HS256 알고리즘을 사용하여 검증기 생성
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer("auth0");
        
        // 토큰 검증
        verifier.verify(decoded);
        
        // 클레임을 JSON 문자열로 변환하여 반환
        std::string result = "{";
        bool first = true;
        
        for (auto& [key, value] : decoded.get_payload_claims()) {
            if (!first) {
                result += ",";
            }
            first = false;
            
            result += "\"" + key + "\":";
            
            // 클레임 값의 타입에 따라 적절한 형식으로 변환
            if (value.get_type() == jwt::json::type::string) {
                result += "\"" + value.as_string() + "\"";
            } else if (value.get_type() == jwt::json::type::integer) {
                result += std::to_string(value.as_int());
            } else if (value.get_type() == jwt::json::type::number) {
                result += std::to_string(value.as_number());
            } else if (value.get_type() == jwt::json::type::boolean) {
                result += value.as_bool() ? "true" : "false";
            } else {
                // 기타 타입은 문자열로 변환
                result += "\"" + value.to_json().to_str() + "\"";
            }
        }
        
        result += "}";
        return result;
        
    } catch (const jwt::error::token_verification_exception& e) {
        // 토큰 검증 실패
        std::cerr << "Token verification failed: " << e.what() << std::endl;
    } catch (const jwt::error::signature_verification_exception& e) {
        // 서명 검증 실패
        std::cerr << "Signature verification failed: " << e.what() << std::endl;
    } catch (const jwt::error::rsa_exception& e) {
        // RSA 관련 오류
        std::cerr << "RSA error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        // 기타 모든 예외
        std::cerr << "Error decoding JWT: " << e.what() << std::endl;
    }
    
    // 모든 예외 상황에서 빈 JSON 객체 반환
    return "{}";
}