#include <jwt.h>
#include <string>
#include <stdexcept>
#include <iostream>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // jwt-cpp 라이브러리를 사용하여 토큰 디코딩
        auto decoded = jwt::decode(token);
        
        // HS256 알고리즘을 사용하여 토큰 검증
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer("auth0");
        
        // 토큰 검증 수행
        verifier.verify(decoded);
        
        // 클레임을 JSON 문자열로 변환
        std::string result = "{";
        bool first = true;
        
        for (auto& claim : decoded.get_payload_claims()) {
            if (!first) {
                result += ",";
            }
            result += "\"" + claim.first + "\":";
            
            // 클레임 타입에 따라 적절한 형식으로 추가
            if (claim.second.get_type() == jwt::json::type::string) {
                result += "\"" + claim.second.as_string() + "\"";
            } else if (claim.second.get_type() == jwt::json::type::integer) {
                result += std::to_string(claim.second.as_int());
            } else if (claim.second.get_type() == jwt::json::type::number) {
                result += std::to_string(claim.second.as_number());
            } else if (claim.second.get_type() == jwt::json::type::boolean) {
                result += claim.second.as_bool() ? "true" : "false";
            } else {
                // 기타 타입은 문자열로 처리
                result += "\"" + claim.second.to_json().to_str() + "\"";
            }
            
            first = false;
        }
        result += "}";
        
        return result;
    } catch (const jwt::error::token_verification_exception& e) {
        // 토큰 검증 실패 시 빈 JSON 객체 반환
        return "{}";
    } catch (const std::exception& e) {
        // 기타 예외 발생 시 빈 JSON 객체 반환
        return "{}";
    }
}