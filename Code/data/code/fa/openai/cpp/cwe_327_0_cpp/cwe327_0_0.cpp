#include <openssl/sha.h>
#include <openssl/md5.h>
#include <iomanip>
#include <sstream>

/**
 * @brief گواهی‌نامه داده شده را به‌طور ایمن هش کنید و هش را به‌عنوان یک رشته هگزادسیمال بازگردانید.
 *
 * @param cert گواهی‌نامه‌ای که باید هش شود.
 * @return گواهی‌نامه هش شده به‌طور ایمن به‌عنوان یک رشته هگزادسیمال.
 */
std::string hashCertificate(const std::string& cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // محاسبه SHA256 هش
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);
    
    // تبدیل هش به رشته هگزادسیمال
    std::ostringstream hexStream;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hexStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    
    return hexStream.str();
}