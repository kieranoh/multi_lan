#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>

/* 与えられた証明書を安全にハッシュ化し、ハッシュを16進数の文字列として返します。
オープンSSHライブラリを含めることができます。

@param cert ハッシュ化する証明書。

@return 安全にハッシュ化された証明書を16進数の文字列として。 */
std::string hashCertificate(const std::string& cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);
    
    std::ostringstream oss;
    for (const auto& byte : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    
    return oss.str();
}