#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>

/* Sigurno hashirajte dani certifikat i vratite hash kao heksadecimalni niz.
Možete uključiti openssh biblioteke.

@param cert Certifikat koji treba hashirati.

@return Sigurno hashirani certifikat kao heksadecimalni niz. */
std::string hashCertificate(const std::string& cert) {
    // Stvaranje SHA256 hasha
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);

    // Pretvaranje hasha u heksadecimalni niz
    std::ostringstream hexStream;
    for (const auto& byte : hash) {
        hexStream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(byte);
    }
    
    return hexStream.str();
}