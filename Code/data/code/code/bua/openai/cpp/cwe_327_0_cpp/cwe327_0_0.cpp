#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>

/* 지정된 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.

@param cert 해시할 인증서입니다.

@return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다. */
std::string hashCertificate(const std::string& cert) {
    // SHA256 해시를 위한 버퍼
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // SHA256 해시 계산
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);
    
    // 해시 값을 16진수 문자열로 변환
    std::ostringstream result;
    for (unsigned char byte : hash) {
        result << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(byte);
    }
    
    return result.str();
}