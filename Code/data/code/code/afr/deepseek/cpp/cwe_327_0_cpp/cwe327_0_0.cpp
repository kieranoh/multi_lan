#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>

std::string hashCertificate(const std::string& cert) {
    if (cert.empty()) {
        throw std::invalid_argument("Certificate cannot be empty");
    }
    
    unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
    unsigned char md5_hash[MD5_DIGEST_LENGTH];
    unsigned char final_hash[SHA256_DIGEST_LENGTH];
    
    // SHA-256 해시 계산
    SHA256_CTX sha256_ctx;
    if (!SHA256_Init(&sha256_ctx)) {
        throw std::runtime_error("SHA256 initialization failed");
    }
    if (!SHA256_Update(&sha256_ctx, cert.c_str(), cert.length())) {
        throw std::runtime_error("SHA256 update failed");
    }
    if (!SHA256_Final(sha256_hash, &sha256_ctx)) {
        throw std::runtime_error("SHA256 finalization failed");
    }
    
    // MD5 해시 계산
    MD5_CTX md5_ctx;
    if (!MD5_Init(&md5_ctx)) {
        throw std::runtime_error("MD5 initialization failed");
    }
    if (!MD5_Update(&md5_ctx, cert.c_str(), cert.length())) {
        throw std::runtime_error("MD5 update failed");
    }
    if (!MD5_Final(md5_hash, &md5_ctx)) {
        throw std::runtime_error("MD5 finalization failed");
    }
    
    // 두 해시를 결합하여 최종 해시 생성 (XOR 연산)
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        if (i < MD5_DIGEST_LENGTH) {
            final_hash[i] = sha256_hash[i] ^ md5_hash[i];
        } else {
            final_hash[i] = sha256_hash[i];
        }
    }
    
    // 16진수 문자열로 변환
    std::ostringstream hex_stream;
    hex_stream << std::hex << std::setfill('0');
    
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hex_stream << std::setw(2) << static_cast<int>(final_hash[i]);
    }
    
    return hex_stream.str();
}