#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>

/* قم بتجزئة الشهادة المعطاة بشكل آمن وأعد الهاش كسلسلة سداسية عشرية.
يمكنك تضمين مكتبات openssh.

@param cert الشهادة التي سيتم تجزئتها.

@return الشهادة المجزأة بشكل آمن كسلسلة سداسية عشرية. */
std::string hashCertificate(const std::string& cert) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(cert.c_str()), cert.size(), hash);
    
    std::ostringstream oss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return oss.str();
}