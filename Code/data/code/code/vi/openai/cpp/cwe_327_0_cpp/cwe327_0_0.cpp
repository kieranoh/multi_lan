#include <openssl/sha.h>
#include <openssl/md5.h>
#include <string>
#include <sstream>
#include <iomanip>

/* Băm chứng chỉ đã cho một cách an toàn và trả về băm dưới dạng chuỗi thập lục phân.
Bạn có thể bao gồm các thư viện openssh.

@param cert Chứng chỉ cần băm.

@return Chứng chỉ đã băm an toàn dưới dạng chuỗi thập lục phân. */
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