#include <jwt.h>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <stdexcept>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // jwt-cpp 라이브러리를 사용하여 토큰 디코딩
        auto decoded = jwt::decode(token);
        
        // HS256 알고리즘을 사용하여 토큰 검증
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer(decoded.get_issuer());
        
        // 토큰 검증
        verifier.verify(decoded);
        
        // 클레임을 JSON 형식으로 변환
        std::ostringstream json_stream;
        json_stream << "{";
        
        bool first = true;
        for (const auto& claim_pair : decoded.get_payload_claims()) {
            if (!first) {
                json_stream << ",";
            }
            first = false;
            
            json_stream << "\"" << claim_pair.first << "\":";
            
            // 클레임 타입에 따라 적절한 형식으로 출력
            if (claim_pair.second.get_type() == jwt::json::type::string) {
                json_stream << "\"" << claim_pair.second.as_string() << "\"";
            } else if (claim_pair.second.get_type() == jwt::json::type::integer) {
                json_stream << claim_pair.second.as_int();
            } else if (claim_pair.second.get_type() == jwt::json::type::number) {
                json_stream << claim_pair.second.as_number();
            } else if (claim_pair.second.get_type() == jwt::json::type::boolean) {
                json_stream << (claim_pair.second.as_bool() ? "true" : "false");
            } else {
                // 배열이나 객체인 경우 JSON 문자열로 처리
                json_stream << "\"" << claim_pair.second.to_json().dump() << "\"";
            }
        }
        
        json_stream << "}";
        return json_stream.str();
        
    } catch (const jwt::error::token_verification_exception& e) {
        // 토큰 검증 실패
        std::cerr << "Token verification failed: " << e.what() << std::endl;
    } catch (const jwt::error::signature_verification_exception& e) {
        // 서명 검증 실패
        std::cerr << "Signature verification failed: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        // 기타 예외
        std::cerr << "Decoding failed: " << e.what() << std::endl;
    }
    
    // 디코딩 실패 시 빈 JSON 객체 반환
    return "{}";
}