#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <memory>

/* 지정된 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.

@param cert 해시할 인증서입니다.

@return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다. */
std::string hashCertificate(const std::string& cert) {
    // SHA-256 해시 컨텍스트 생성
    std::unique_ptr<SHA256_CTX> sha256_ctx = std::make_unique<SHA256_CTX>();
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // SHA-256 해시 초기화
    if (!SHA256_Init(sha256_ctx.get())) {
        return ""; // 초기화 실패 시 빈 문자열 반환
    }
    
    // 데이터 업데이트
    if (!SHA256_Update(sha256_ctx.get(), cert.c_str(), cert.length())) {
        return ""; // 업데이트 실패 시 빈 문자열 반환
    }
    
    // 해시 최종화
    if (!SHA256_Final(hash, sha256_ctx.get())) {
        return ""; // 최종화 실패 시 빈 문자열 반환
    }
    
    // 16진수 문자열로 변환
    std::ostringstream hex_stream;
    hex_stream << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hex_stream << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return hex_stream.str();
}