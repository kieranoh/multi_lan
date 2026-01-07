#include <openssl/sha.h>
#include <openssl/md5.h>
#include <iomanip>
#include <sstream>

/* Hashea el certificado dado de forma segura y devuelve el hash como una cadena hexadecimal.
Puedes incluir bibliotecas de openssh.

@param cert El certificado que se va a hashear.

@return El certificado hasheado de forma segura como una cadena hexadecimal. */
std::string hashCertificate(const std::string& cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);

    std::stringstream hexStream;
    hexStream << std::hex << std::setfill('0');
    for (const auto& byte : hash) {
        hexStream << std::setw(2) << static_cast<int>(byte);
    }
    return hexStream.str();
}