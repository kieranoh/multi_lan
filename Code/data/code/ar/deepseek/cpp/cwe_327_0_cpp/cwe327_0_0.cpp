#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>

std::string hashCertificate(const std::string& cert) {
    unsigned char sha256_hash[SHA256_DIGEST_LENGTH];
    
    // استخدام SHA256 لتجزئة الشهادة
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, cert.c_str(), cert.length());
    SHA256_Final(sha256_hash, &sha256_ctx);
    
    // تحويل الهاش إلى سلسلة سداسية عشرية
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::setw(2) << static_cast<unsigned int>(sha256_hash[i]);
    }
    
    return ss.str();
}