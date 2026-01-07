#include <jwt.h>
#include <iostream>
#include <string>
#include <cstring>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <vector>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

// Base64 URL 디코딩 함수
std::string base64url_decode(const std::string& encoded) {
    std::string base64 = encoded;
    std::replace(base64.begin(), base64.end(), '-', '+');
    std::replace(base64.begin(), base64.end(), '_', '/');
    
    // 패딩 추가
    switch (base64.length() % 4) {
        case 2: base64 += "=="; break;
        case 3: base64 += "="; break;
    }
    
    // Base64 디코딩
    BIO* b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO* bmem = BIO_new_mem_buf(base64.data(), base64.length());
    bmem = BIO_push(b64, bmem);
    
    std::vector<char> buffer(base64.length());
    int decoded_length = BIO_read(bmem, buffer.data(), buffer.size());
    BIO_free_all(bmem);
    
    if (decoded_length <= 0) {
        return "";
    }
    
    return std::string(buffer.data(), decoded_length);
}

// Base64 URL 인코딩 함수
std::string base64url_encode(const std::string& data) {
    BIO* b64 = BIO_new(BIO_f_base64());
    BIO* bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(b64, data.data(), data.length());
    BIO_flush(b64);
    
    BUF_MEM* bptr;
    BIO_get_mem_ptr(b64, &bptr);
    
    std::string encoded(bptr->data, bptr->length);
    
    // URL-safe 변환
    std::replace(encoded.begin(), encoded.end(), '+', '-');
    std::replace(encoded.begin(), encoded.end(), '/', '_');
    encoded.erase(std::remove(encoded.begin(), encoded.end(), '='), encoded.end());
    
    BIO_free_all(b64);
    return encoded;
}

// HMAC SHA256 서명 생성
std::string hmac_sha256(const std::string& key, const std::string& data) {
    unsigned char* digest = HMAC(EVP_sha256(), 
                                 key.data(), key.length(),
                                 reinterpret_cast<const unsigned char*>(data.data()), 
                                 data.length(),
                                 NULL, NULL);
    
    std::string result(reinterpret_cast<char*>(digest), SHA256_DIGEST_LENGTH);
    return result;
}

// 문자열 분할 함수
std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string decode_json_web_token(const std::string& token, const std::string& key) {
    try {
        // 토큰을 세 부분으로 분리
        std::vector<std::string> parts = split(token, '.');
        if (parts.size() != 3) {
            return "{}";
        }
        
        std::string header_encoded = parts[0];
        std::string payload_encoded = parts[1];
        std::string signature_encoded = parts[2];
        
        // 헤더 디코딩 및 확인
        std::string header_decoded = base64url_decode(header_encoded);
        if (header_decoded.empty()) {
            return "{}";
        }
        
        // 헤더에서 알고리즘 확인 (간단한 확인)
        if (header_decoded.find("HS256") == std::string::npos) {
            return "{}";
        }
        
        // 서명 검증
        std::string data_to_verify = header_encoded + "." + payload_encoded;
        std::string expected_signature = hmac_sha256(key, data_to_verify);
        std::string expected_signature_encoded = base64url_encode(expected_signature);
        
        // 서명 비교
        if (expected_signature_encoded != signature_encoded) {
            return "{}";
        }
        
        // 페이로드 디코딩
        std::string payload_decoded = base64url_decode(payload_encoded);
        if (payload_decoded.empty()) {
            return "{}";
        }
        
        return payload_decoded;
        
    } catch (const std::exception& e) {
        // 모든 예외를 잡아서 빈 JSON 객체 반환
        return "{}";
    } catch (...) {
        // 알 수 없는 예외 처리
        return "{}";
    }
}