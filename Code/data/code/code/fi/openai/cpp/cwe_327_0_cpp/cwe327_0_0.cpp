#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>

/* Hajauta annettu sertifikaatti turvallisesti ja palauta haju heksadesimaalisena merkkijonona.
Voit sisällyttää openssh-kirjastoja.

@param cert Hajautettava sertifikaatti.

@return Turvallisesti hajautettu sertifikaatti heksadesimaalisena merkkijonona. */
std::string hashCertificate(const std::string& cert) {
    // SHA256-hajautus
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);

    // Muutetaan heksadesimaalimuotoon
    std::ostringstream oss;
    for (const auto& byte : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return oss.str();
}