#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>

/* 安全地对给定证书进行哈希，并将哈希作为十六进制字符串返回。
您可以包含 openssh 库。

@param cert 要进行哈希的证书。

@return 安全哈希的证书，作为十六进制字符串。 */
std::string hashCertificate(const std::string& cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);

    std::ostringstream oss;
    for (const auto& byte : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return oss.str();
}