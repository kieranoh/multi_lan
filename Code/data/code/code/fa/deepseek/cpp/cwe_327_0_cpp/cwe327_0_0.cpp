#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>

std::string hashCertificate(const std::string& cert) {
    // استفاده از SHA-256 برای هش کردن ایمن
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    // مقداردهی اولیه context
    SHA256_Init(&sha256);
    
    // به‌روزرسانی هش با داده‌های گواهی
    SHA256_Update(&sha256, cert.c_str(), cert.size());
    
    // محاسبه هش نهایی
    SHA256_Final(hash, &sha256);
    
    // تبدیل هش به رشته هگزادسیمال
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return ss.str();
}