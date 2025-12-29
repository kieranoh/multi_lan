#include <openssl/sha.h>
#include <openssl/md5.h>
#include <iomanip>
#include <sstream>

/* Hasheja el certificat donat de manera segura i retorna el hash com una cadena hexadecimal.
Pots incloure biblioteques d'openssh.

@param cert El certificat que s'ha de hashear.

@return El certificat hashejat de manera segura com una cadena hexadecimal. */
std::string hashCertificate(const std::string& cert) {
    // Crear un buffer per emmagatzemar el hash SHA256
    unsigned char hash[SHA256_DIGEST_LENGTH];

    // Calcular el hash SHA256 del certificat
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);

    // Convertir el hash a una cadena hexadecimal
    std::stringstream hexStream;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    // Retornar el hash en format hex
    return hexStream.str();
}