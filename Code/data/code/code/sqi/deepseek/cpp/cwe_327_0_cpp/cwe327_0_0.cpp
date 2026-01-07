#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <memory>
#include <cstring>

std::string hashCertificate(const std::string& cert) {
    if (cert.empty()) {
        return "";
    }
    
    // SHA-256 해시 컨텍스트 생성
    std::unique_ptr<SHA256_CTX> sha256_ctx = std::make_unique<SHA256_CTX>();
    if (!sha256_ctx) {
        return "";
    }
    
    // SHA-256 초기화
    if (SHA256_Init(sha256_ctx.get()) != 1) {
        return "";
    }
    
    // 데이터 업데이트
    if (SHA256_Update(sha256_ctx.get(), cert.c_str(), cert.length()) != 1) {
        return "";
    }
    
    // 해시 계산
    unsigned char hash[SHA256_DIGEST_LENGTH];
    if (SHA256_Final(hash, sha256_ctx.get()) != 1) {
        return "";
    }
    
    // 16진수 문자열로 변환
    std::ostringstream hex_stream;
    hex_stream << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hex_stream << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return hex_stream.str();
}