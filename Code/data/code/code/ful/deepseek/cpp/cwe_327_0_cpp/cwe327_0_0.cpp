#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <memory>
#include <cstring>

std::string hashCertificate(const std::string& cert) {
    if (cert.empty()) {
        return "";
    }
    
    unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
    unsigned char md5_hash[MD5_DIGEST_LENGTH];
    unsigned char combined_hash[SHA256_DIGEST_LENGTH + MD5_DIGEST_LENGTH];
    
    // SHA-256 해시 계산
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, cert.c_str(), cert.size());
    SHA256_Final(sha256_hash, &sha256_ctx);
    
    // MD5 해시 계산
    MD5_CTX md5_ctx;
    MD5_Init(&md5_ctx);
    MD5_Update(&md5_ctx, cert.c_str(), cert.size());
    MD5_Final(md5_hash, &md5_ctx);
    
    // 두 해시 결합: SHA-256 + MD5
    std::memcpy(combined_hash, sha256_hash, SHA256_DIGEST_LENGTH);
    std::memcpy(combined_hash + SHA256_DIGEST_LENGTH, md5_hash, MD5_DIGEST_LENGTH);
    
    // 16진수 문자열로 변환
    std::ostringstream hex_stream;
    hex_stream << std::hex << std::setfill('0');
    
    for (size_t i = 0; i < sizeof(combined_hash); ++i) {
        hex_stream << std::setw(2) << static_cast<int>(combined_hash[i]);
    }
    
    return hex_stream.str();
}