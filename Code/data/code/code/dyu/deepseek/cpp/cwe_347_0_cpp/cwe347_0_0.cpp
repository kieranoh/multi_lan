#include <jwt.h>
#include <string>
#include <map>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <cstring>
#include <vector>
#include <algorithm>

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    // 빈 토큰이나 키가 주어지면 빈 JSON 객체 반환
    if (token.empty() || key.empty()) {
        return "{}";
    }

    // JWT는 세 부분으로 구성됨: 헤더.페이로드.서명
    std::vector<std::string> parts;
    std::stringstream tokenStream(token);
    std::string part;
    
    while (std::getline(tokenStream, part, '.')) {
        parts.push_back(part);
    }

    // JWT는 정확히 3부분이어야 함
    if (parts.size() != 3) {
        return "{}";
    }

    const std::string& headerBase64 = parts[0];
    const std::string& payloadBase64 = parts[1];
    const std::string& signatureBase64 = parts[2];

    // Base64Url 디코딩 함수
    auto base64UrlDecode = [](const std::string& input) -> std::string {
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
        // 여기서는 단순화를 위해 원본을 반환
        return base64;
    };

    // HMAC SHA256 검증
    auto verifySignature = [&](const std::string& data, const std::string& signature, const std::string& key) -> bool {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        
        HMAC_CTX* ctx = HMAC_CTX_new();
        HMAC_Init_ex(ctx, key.c_str(), key.length(), EVP_sha256(), NULL);
        HMAC_Update(ctx, reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
        unsigned int len;
        HMAC_Final(ctx, hash, &len);
        HMAC_CTX_free(ctx);
        
        // 서명 비교 (타이밍 공격 방지를 위해 상수 시간 비교가 이상적)
        std::string calculatedSignature(reinterpret_cast<char*>(hash), SHA256_DIGEST_LENGTH);
        return calculatedSignature == signature;
    };

    try {
        // 서명 검증
        std::string dataToVerify = headerBase64 + "." + payloadBase64;
        std::string signature = base64UrlDecode(signatureBase64);
        
        if (!verifySignature(dataToVerify, signature, key)) {
            return "{}";
        }

        // 페이로드 디코딩
        std::string decodedPayload = base64UrlDecode(payloadBase64);
        
        // 디코딩된 페이로드가 유효한 JSON인지 확인
        // 실제 구현에서는 JSON 파싱 라이브러리를 사용해야 함
        // 여기서는 단순화를 위해 디코딩된 문자열을 반환
        if (decodedPayload.empty()) {
            return "{}";
        }
        
        return decodedPayload;
        
    } catch (const std::exception& e) {
        // 모든 예외를 잡아 빈 JSON 객체 반환
        return "{}";
    } catch (...) {
        // 알 수 없는 예외 처리
        return "{}";
    }
}