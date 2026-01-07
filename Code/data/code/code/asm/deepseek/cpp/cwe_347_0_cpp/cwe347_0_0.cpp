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
    // 빈 토큰이나 키가 주어지면 빈 JSON 객체 반환
    if (token.empty() || key.empty()) {
        return "{}";
    }

    try {
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
        auto base64UrlDecode = [](const std::string& input) -> std::string {
            std::string base64 = input;
            
            // Base64Url을 Base64로 변환
            std::replace(base64.begin(), base64.end(), '-', '+');
            std::replace(base64.begin(), base64.end(), '_', '/');
            
            // 패딩 추가
            switch (base64.length() % 4) {
                case 2: base64 += "=="; break;
                case 3: base64 += "="; break;
                default: break;
            }
            
            // Base64 디코딩
            return jwt::base64_urldecode(base64);
        };

        // 헤더와 페이로드 디코딩
        std::string headerJson = base64UrlDecode(parts[0]);
        std::string payloadJson = base64UrlDecode(parts[1]);
        
        // JSON 파싱
        Json::Value header, payload;
        Json::CharReaderBuilder readerBuilder;
        std::string errors;
        
        std::stringstream headerStream(headerJson);
        std::stringstream payloadStream(payloadJson);
        
        if (!Json::parseFromStream(readerBuilder, headerStream, &header, &errors)) {
            return "{}";
        }
        
        if (!Json::parseFromStream(readerBuilder, payloadStream, &payload, &errors)) {
            return "{}";
        }
        
        // 알고리즘 확인 (HS256만 지원)
        if (!header.isMember("alg") || header["alg"].asString() != "HS256") {
            return "{}";
        }
        
        // 서명 검증
        std::string dataToSign = parts[0] + "." + parts[1];
        
        // HMAC-SHA256 서명 생성
        unsigned char hash[SHA256_DIGEST_LENGTH];
        unsigned int hashLen;
        
        HMAC(EVP_sha256(), 
             key.c_str(), static_cast<int>(key.length()),
             reinterpret_cast<const unsigned char*>(dataToSign.c_str()), dataToSign.length(),
             hash, &hashLen);
        
        // 생성된 서명을 Base64Url로 인코딩
        std::stringstream signatureStream;
        for (unsigned int i = 0; i < hashLen; i++) {
            signatureStream << std::hex << std::setw(2) << std::setfill('0') 
                          << static_cast<int>(hash[i]);
        }
        
        std::string hexSignature = signatureStream.str();
        std::string calculatedSignature = jwt::base64url_encode(hexSignature);
        
        // 서명 비교
        if (calculatedSignature != parts[2]) {
            return "{}";
        }
        
        // 페이로드를 JSON 문자열로 변환하여 반환
        Json::StreamWriterBuilder writerBuilder;
        writerBuilder["indentation"] = ""; // 압축된 JSON
        return Json::writeString(writerBuilder, payload);
        
    } catch (const std::exception& e) {
        // 모든 예외를 잡아 빈 JSON 객체 반환
        return "{}";
    } catch (...) {
        // 알 수 없는 예외 처리
        return "{}";
    }
}