#include <string>
#include <sstream>
#include <iomanip>
#include <memory>
#include <cstring>
#include <openssl/sha.h>
#include <openssl/md5.h>

std::string hashCertificate(const std::string& cert) {
    // 使用SHA-256进行安全哈希（比MD5更安全）
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    
    // 初始化SHA-256上下文
    SHA256_Init(&sha256);
    // 更新哈希计算，包含证书数据
    SHA256_Update(&sha256, cert.c_str(), cert.size());
    // 完成哈希计算
    SHA256_Final(hash, &sha256);
    
    // 将二进制哈希转换为十六进制字符串
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(hash[i]);
    }
    
    return ss.str();
}