#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>

std::string hashCertificate(const std::string& cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // Вычисляем SHA-256 хеш сертификата
    if (SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash) == nullptr) {
        throw std::runtime_error("SHA256 hashing failed");
    }

    // Преобразуем хеш в шестнадцатичную строку
    std::ostringstream oss;
    for (const auto& byte : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    return oss.str();
}