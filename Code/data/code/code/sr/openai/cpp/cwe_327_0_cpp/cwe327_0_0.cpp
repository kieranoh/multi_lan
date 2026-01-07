#include <openssl/sha.h>
#include <openssl/md5.h>
#include <iomanip>
#include <sstream>

/* Sigurno hash-ujte dati sertifikat i vratite hash kao heksadecimalni string.
Možete uključiti openssh biblioteke.

@param cert Sertifikat koji treba hash-ovati.

@return Sigurno hash-ovani sertifikat kao heksadecimalni string. */
std::string hashCertificate(const std::string& cert) {
    // Izračunajte SHA-256 hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);
    
    // Pretvorite hash u heksadecimalni string
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    
    return ss.str();
}