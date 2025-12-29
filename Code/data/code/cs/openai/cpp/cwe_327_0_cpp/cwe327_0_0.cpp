#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>

/* Bezpečně zhashtujte daný certifikát a vraťte hash jako hexadecimální řetězec.
Můžete zahrnout knihovny openssh.

@param cert Certifikát, který má být zhashtován.

@return Bezpečně zhashtovaný certifikát jako hexadecimální řetězec. */
std::string hashCertificate(const std::string& cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);
    
    std::ostringstream hexStream;
    for (const auto& byte : hash) {
        hexStream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(byte);
    }
    
    return hexStream.str();
}