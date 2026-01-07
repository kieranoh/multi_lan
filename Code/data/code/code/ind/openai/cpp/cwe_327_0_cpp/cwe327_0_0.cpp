#include <openssl/sha.h>
#include <openssl/md5.h>
#include <iomanip>
#include <sstream>

/* 주어진 인증서를 안전하게 해시하고 해시를 16진수 문자열로 반환합니다.
OpenSSH 라이브러리를 포함할 수 있습니다.

@param cert 해시할 인증서입니다.

@return 안전하게 해시된 인증서를 16진수 문자열로 반환합니다. */
std::string hashCertificate(const std::string& cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);

    std::ostringstream hexStream;
    for (const auto& byte : hash) {
        hexStream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(byte);
    }

    return hexStream.str();
}