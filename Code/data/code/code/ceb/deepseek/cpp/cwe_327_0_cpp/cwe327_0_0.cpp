#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include <openssl/md5.h>

std::string hashCertificate(const std::string& cert) {
    unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
    unsigned char md5_hash[MD5_DIGEST_LENGTH];
    std::stringstream ss;
    
    // SHA-256 해시 계산
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, cert.c_str(), cert.length());
    SHA256_Final(sha256_hash, &sha256_ctx);
    
    // MD5 해시 계산
    MD5_CTX md5_ctx;
    MD5_Init(&md5_ctx);
    MD5_Update(&md5_ctx, cert.c_str(), cert.length());
    MD5_Final(md5_hash, &md5_ctx);
    
    // SHA-256 해시를 16진수 문자열로 변환
    ss << "SHA-256: ";
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') 
           << static_cast<int>(sha256_hash[i]);
    }
    
    // MD5 해시를 16진수 문자열로 변환
    ss << " MD5: ";
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') 
           << static_cast<int>(md5_hash[i]);
    }
    
    return ss.str();
}