#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>

/* 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.

@param cert 해시할 인증서.

@return 안전하게 해시된 인증서의 16진수 문자열. */
std::string hashCertificate(const std::string& cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);

    std::stringstream hexString;
    for (unsigned char i : hash) {
        hexString << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);
    }
    
    return hexString.str();
}