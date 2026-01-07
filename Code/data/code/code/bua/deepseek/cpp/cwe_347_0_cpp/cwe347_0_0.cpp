#include <jwt.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include <json/json.h>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // JWT 디코딩을 위한 객체 생성
        auto decoded = jwt::decode(token);
        
        // HS256 알고리즘을 사용하여 검증
        auto verifier = jwt::verify()
            .allow_algorithm(jwt::algorithm::hs256{key})
            .with_issuer("auth0");
        
        // 토큰 검증
        verifier.verify(decoded);
        
        // 클레임을 JSON 객체로 변환
        Json::Value claims;
        for (const auto& claim : decoded.get_payload_claims()) {
            const std::string& name = claim.first;
            const jwt::claim& c = claim.second;
            
            // 클레임 타입에 따라 적절히 처리
            if (c.get_type() == jwt::claim::type::boolean) {
                claims[name] = c.as_bool();
            } else if (c.get_type() == jwt::claim::type::integer) {
                claims[name] = c.as_int();
            } else if (c.get_type() == jwt::claim::type::number) {
                claims[name] = c.as_number();
            } else if (c.get_type() == jwt::claim::type::string) {
                claims[name] = c.as_string();
            } else if (c.get_type() == jwt::claim::type::array) {
                Json::Value array(Json::arrayValue);
                auto arr = c.as_array();
                for (const auto& item : arr) {
                    if (item.is_string()) {
                        array.append(item.get<std::string>());
                    } else if (item.is_number()) {
                        array.append(item.get<double>());
                    } else if (item.is_boolean()) {
                        array.append(item.get<bool>());
                    } else if (item.is_integer()) {
                        array.append(item.get<int64_t>());
                    }
                }
                claims[name] = array;
            } else if (c.get_type() == jwt::claim::type::object) {
                // 객체 타입의 클레임은 문자열로 직렬화
                claims[name] = c.to_json().dump();
            }
        }
        
        // JSON을 문자열로 변환하여 반환
        Json::StreamWriterBuilder writer;
        writer["indentation"] = ""; // 압축된 형식
        return Json::writeString(writer, claims);
        
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
        // 기타 예외
        std::cerr << "Decoding error: " << e.what() << std::endl;
    }
    
    // 실패 시 빈 JSON 객체 반환
    return "{}";
}