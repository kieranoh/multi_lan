#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <string>

/* Hasha det angivna certifikatet på ett säkert sätt och returnera hashvärdet som en hexadecimalt sträng.
   @param cert Certifikatet som ska hashats.
   @return Det säkert hashade certifikatet som en hexadecimalt sträng. */
std::string hashCertificate(const std::string& cert) {
    // Skapa en array för SHA256-hash
    unsigned char hash[SHA256_DIGEST_LENGTH];

    // Beräkna SHA256-hashen av certifikatet
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);

    // Konvertera hashvärdet till en hexadecimalt sträng
    std::ostringstream hexStream;
    for (const auto& byte : hash) {
        hexStream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(byte);
    }

    return hexStream.str();
}