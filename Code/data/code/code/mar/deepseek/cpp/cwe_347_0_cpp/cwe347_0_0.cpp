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
            .with_issuer("issuer"); // 필요에 따라 다른 클레임 검증 추가 가능
            
        verifier.verify(decoded);
        
        // 페이로드 클레임을 JSON 문자열로 변환
        std::string result = "{";
        bool first = true;
        
        for (auto& [key, value] : decoded.get_payload_json()) {
            if (!first) {
                result += ",";
            }
            result += "\"" + key + "\":" + value.to_string();
            first = false;
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
        // RSA 관련 오류 (HS256에는 해당되지 않지만 안전을 위해)
        return "{}";
    } catch (const std::exception& e) {
        // 기타 모든 예외
        return "{}";
    }
}