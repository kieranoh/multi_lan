#include <openssl/sha.h>
#include <openssl/md5.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstring>

std::string hashCertificate(const std::string& cert) {
    // Sử dụng SHA-256 để băm an toàn
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    // Khởi tạo context SHA-256
    if (!SHA256_Init(&sha256)) {
        // Trả về chuỗi rỗng nếu khởi tạo thất bại
        return "";
    }
    
    // Cập nhật dữ liệu cần băm
    if (!SHA256_Update(&sha256, cert.c_str(), cert.length())) {
        // Trả về chuỗi rỗng nếu cập nhật thất bại
        return "";
    }
    
    // Lấy kết quả băm
    if (!SHA256_Final(hash, &sha256)) {
        // Trả về chuỗi rỗng nếu lấy kết quả thất bại
        return "";
    }
    
    // Chuyển đổi kết quả băm thành chuỗi hex
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return ss.str();
}