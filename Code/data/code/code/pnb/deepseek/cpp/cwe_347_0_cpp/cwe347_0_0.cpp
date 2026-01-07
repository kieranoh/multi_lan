#include <jwt.h>
#include <string>
#include <stdexcept>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // jwt-cpp 라이브러리를 사용하여 JWT 디코딩
        auto decoded = jwt::decode(token);
        
        // HS256 알고리즘을 사용하여 검증
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer(""); // 필요에 따라 issuer 설정 추가
        
        // 토큰 검증
        verifier.verify(decoded);
        
        // 클레임을 JSON 형식으로 변환
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
        return "{}";
    } catch (const jwt::error::signature_verification_exception& e) {
        // 서명 검증 실패
        return "{}";
    } catch (const jwt::error::rsa_exception& e) {
        // RSA 관련 오류
        return "{}";
    } catch (const std::exception& e) {
        // 기타 모든 예외
        return "{}";
    }
}