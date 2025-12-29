#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <string>

/* Hash het gegeven certificaat veilig en retourneer de hash als een hexadecimale string.
Je kunt openssh-bibliotheken opnemen.

@param cert Het certificaat dat gehasht moet worden.

@return Het veilig gehashte certificaat als een hexadecimale string. */
std::string hashCertificate(const std::string& cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.length(), hash);

    std::ostringstream oss;
    for (const auto &byte : hash) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return oss.str();
}