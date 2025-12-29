#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>

/* Hashen Sie das gegebene Zertifikat sicher und geben Sie den Hash als hexadezimale Zeichenkette zurück.
Sie können OpenSSH-Bibliotheken einbeziehen.

@param cert Das zu hashende Zertifikat.

@return Das sicher gehashte Zertifikat als hexadezimale Zeichenkette. */
std::string hashCertificate(const std::string& cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);
    
    std::ostringstream hexStream;
    for (const auto& byte : hash) {
        hexStream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(byte);
    }
    
    return hexStream.str();
}