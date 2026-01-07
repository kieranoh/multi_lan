#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>

std::string hashCertificate(const std::string& cert) {
    // Zainicjuj obiekt SHA256
    unsigned char sha256Hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), sha256Hash);

    // Użyj std::ostringstream do konwersji hash na string w formacie szesnastkowym
    std::ostringstream oss;
    for (const auto& byte : sha256Hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    return oss.str();
}