#include <jwt.h>
#include <stdexcept>
#include <sstream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // JWT 디코딩을 위한 jwt::decode 함수 호출
        auto decoded = jwt::decode(token);
        
        // HS256 알고리즘을 사용하여 토큰 검증
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer("auth0");
        
        // 토큰 검증
        verifier.verify(decoded);
        
        // 클레임을 JSON 형식으로 변환
        std::stringstream ss;
        ss << "{";
        
        bool first = true;
        for (auto& claim : decoded.get_payload_claims()) {
            if (!first) {
                ss << ",";
            }
            first = false;
            
            ss << "\"" << claim.first << "\":";
            
            // 클레임 타입에 따라 적절한 형식으로 출력
            if (claim.second.get_type() == jwt::json::type::string) {
                ss << "\"" << claim.second.as_string() << "\"";
            } else if (claim.second.get_type() == jwt::json::type::integer) {
                ss << claim.second.as_int();
            } else if (claim.second.get_type() == jwt::json::type::number) {
                ss << claim.second.as_number();
            } else if (claim.second.get_type() == jwt::json::type::boolean) {
                ss << (claim.second.as_bool() ? "true" : "false");
            } else {
                // 기타 타입은 문자열로 처리
                ss << "\"" << claim.second.to_json() << "\"";
            }
        }
        
        ss << "}";
        return ss.str();
        
    } catch (const jwt::token_verification_exception& e) {
        // 토큰 검증 실패
        return "{}";
    } catch (const jwt::error::claim_not_present_exception& e) {
        // 필요한 클레임이 없는 경우
        return "{}";
    } catch (const std::exception& e) {
        // 기타 예외 처리
        return "{}";
    }
}