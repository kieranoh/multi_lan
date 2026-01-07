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
    
    unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
    unsigned char md5_hash[MD5_DIGEST_LENGTH];
    unsigned char final_hash[SHA256_DIGEST_LENGTH];
    
    // 1단계: SHA256으로 인증서 해시
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, cert.c_str(), cert.length());
    SHA256_Final(sha256_hash, &sha256_ctx);
    
    // 2단계: SHA256 해시 결과를 MD5로 해시
    MD5_CTX md5_ctx;
    MD5_Init(&md5_ctx);
    MD5_Update(&md5_ctx, sha256_hash, SHA256_DIGEST_LENGTH);
    MD5_Final(md5_hash, &md5_ctx);
    
    // 3단계: SHA256 해시와 MD5 해시를 XOR 결합
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        final_hash[i] = sha256_hash[i] ^ md5_hash[i % MD5_DIGEST_LENGTH];
    }
    
    // 16진수 문자열로 변환
    std::ostringstream hex_stream;
    hex_stream << std::hex << std::setfill('0');
    
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hex_stream << std::setw(2) << static_cast<int>(final_hash[i]);
    }
    
    return hex_stream.str();
}