#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <memory>
#include <cstring>

/* 지정된 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.

@param cert 해시할 인증서입니다.

@return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다. */
std::string hashCertificate(const std::string& cert) {
    // SHA-256 해시 컨텍스트 생성
    std::unique_ptr<SHA256_CTX> sha256_ctx = std::make_unique<SHA256_CTX>();
    
    // SHA-256 컨텍스트 초기화
    if (SHA256_Init(sha256_ctx.get()) != 1) {
        return ""; // 초기화 실패 시 빈 문자열 반환
    }
    
    // 인증서 데이터 업데이트
    if (SHA256_Update(sha256_ctx.get(), cert.data(), cert.size()) != 1) {
        return ""; // 업데이트 실패 시 빈 문자열 반환
    }
    
    // 해시 결과 저장을 위한 버퍼
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // 최종 해시 계산
    if (SHA256_Final(hash, sha256_ctx.get()) != 1) {
        return ""; // 최종 계산 실패 시 빈 문자열 반환
    }
    
    // 16진수 문자열로 변환
    std::ostringstream hex_stream;
    hex_stream << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hex_stream << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return hex_stream.str();
}