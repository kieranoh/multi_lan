#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <memory>

std::string hashCertificate(const std::string& cert) {
    // SHA-256 해시 컨텍스트 생성
    std::unique_ptr<SHA256_CTX> sha256_ctx = std::make_unique<SHA256_CTX>();
    SHA256_Init(sha256_ctx.get());
    
    // 인증서 데이터 해시 처리
    SHA256_Update(sha256_ctx.get(), cert.c_str(), cert.length());
    
    // 해시 결과 저장
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, sha256_ctx.get());
    
    // 16진수 문자열로 변환
    std::ostringstream hex_stream;
    hex_stream << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hex_stream << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return hex_stream.str();
}