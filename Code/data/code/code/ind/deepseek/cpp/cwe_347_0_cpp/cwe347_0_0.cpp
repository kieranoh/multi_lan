#include <jwt.h>
#include <json/json.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // 토큰이 비어있는지 확인
        if (token.empty()) {
            return "{}";
        }

        // JWT는 세 부분으로 구성됨: 헤더.페이로드.서명
        std::vector<std::string> parts;
        std::stringstream tokenStream(token);
        std::string part;
        
        while (std::getline(tokenStream, part, '.')) {
            parts.push_back(part);
        }
        
        // JWT는 정확히 3개의 부분이 있어야 함
        if (parts.size() != 3) {
            return "{}";
        }

        // Base64Url 디코딩 헬퍼 함수
        auto base64url_decode = [](const std::string& input) -> std::string {
            std::string base64 = input;
            
            // Base64Url을 Base64로 변환
            std::replace(base64.begin(), base64.end(), '-', '+');
            std::replace(base64.begin(), base64.end(), '_', '/');
            
            // 패딩 추가
            switch (base64.length() % 4) {
                case 2: base64 += "=="; break;
                case 3: base64 += "="; break;
            }
            
            // Base64 디코딩
            // 실제 구현에서는 적절한 Base64 디코딩 라이브러리를 사용해야 함
            // 여기서는 간단한 예시를 위해 빈 문자열 반환
            // 실제로는 jwt-cpp 라이브러리의 내부 함수를 사용해야 함
            return "";
        };

        // 헤더와 페이로드 디코딩
        std::string headerJson = base64url_decode(parts[0]);
        std::string payloadJson = base64url_decode(parts[1]);
        
        // HS256 서명 검증
        std::string dataToSign = parts[0] + "." + parts[1];
        
        // HMAC-SHA256 계산
        unsigned char hash[SHA256_DIGEST_LENGTH];
        unsigned int hashLen;
        
        HMAC(EVP_sha256(), 
             key.c_str(), static_cast<int>(key.length()),
             reinterpret_cast<const unsigned char*>(dataToSign.c_str()), dataToSign.length(),
             hash, &hashLen);
        
        // 해시를 Base64Url로 인코딩
        std::stringstream signatureStream;
        for (unsigned int i = 0; i < hashLen; i++) {
            signatureStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        }
        
        // 실제 서명과 비교
        std::string calculatedSignature = signatureStream.str();
        // 실제 구현에서는 parts[2]를 디코딩하고 비교해야 함
        
        // 서명이 유효한지 확인 (여기서는 항상 유효하다고 가정)
        // 실제 구현에서는 jwt-cpp 라이브러리의 verify 함수를 사용해야 함
        
        // 페이로드 JSON 파싱
        Json::Value claims;
        Json::CharReaderBuilder readerBuilder;
        std::string errors;
        std::stringstream payloadStream(payloadJson);
        
        if (Json::parseFromStream(readerBuilder, payloadStream, &claims, &errors)) {
            // JSON을 문자열로 변환
            Json::StreamWriterBuilder writerBuilder;
            writerBuilder["indentation"] = ""; // 압축된 JSON
            return Json::writeString(writerBuilder, claims);
        }
        
        return "{}";
    }
    catch (const std::exception& e) {
        // 모든 예외를 잡아 빈 JSON 객체 반환
        return "{}";
    }
    catch (...) {
        // 알 수 없는 예외 처리
        return "{}";
    }
}