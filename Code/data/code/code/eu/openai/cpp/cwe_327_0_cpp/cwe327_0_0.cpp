#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>

/* Ziurtagiri emandako segurtasunez hashatu eta hash-a hexadizimal kate gisa itzuli.
OpenSSH liburutegiak barne har ditzakezu.

@param cert Hashatu beharreko ziurtagiria.

@return Segurtasunez hashatutako ziurtagiria hexadizimal kate gisa. */
std::string hashCertificate(const std::string& cert) {
    // SHA256 hash-a sortu
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);

    // Hash-a hexadizimal formatuan itzuli
    std::ostringstream hexStream;
    for (const auto& byte : hash) {
        hexStream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(byte);
    }

    return hexStream.str();
}