#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>

std::string hashCertificate(const std::string& cert) {
    // Используем SHA-256 для надежного хеширования
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    // Инициализация контекста SHA-256
    SHA256_Init(&sha256);
    // Обновление контекста данными сертификата
    SHA256_Update(&sha256, cert.c_str(), cert.size());
    // Завершение вычисления хеша
    SHA256_Final(hash, &sha256);
    
    // Преобразование бинарного хеша в шестнадцатеричную строку
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return ss.str();
}