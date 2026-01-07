#include <openssl/sha.h>
#include <openssl/md5.h>
#include <iomanip>
#include <sstream>

/* Verilen sertifikayı güvenli bir şekilde hash'leyin ve hash'i onaltılık bir dize olarak döndürün.
OpenSSH kütüphanelerini dahil edebilirsiniz.

@param cert Hash'lenecek sertifika.

@return Güvenli bir şekilde hash'lenmiş sertifika onaltılık bir dize olarak. */
std::string hashCertificate(const std::string& cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);

    std::ostringstream oss;
    for (const auto& byte : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return oss.str();
}