#include <openssl/evp.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstdint>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    // 验证输入参数
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<std::size_t>(count) > usernames.size() || static_cast<std::size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds the size of usernames or passwords vector");
    }
    
    // 定义哈希输出长度（字节）
    constexpr int hash_length = 32; // SHA-256 输出为 32 字节
    
    // 结果向量
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    for (int i = 0; i < count; ++i) {
        // 生成盐：长度与哈希输出相同
        std::vector<unsigned char> salt(hash_length);
        
        // 使用 OpenSSL 的随机数生成器生成盐
        // 注意：在实际应用中，可能需要更安全的随机数生成方式
        if (RAND_bytes(salt.data(), hash_length) != 1) {
            throw std::runtime_error("Failed to generate random salt");
        }
        
        // 准备哈希输出缓冲区
        std::vector<unsigned char> hash(hash_length);
        
        // 使用 PKCS5_PBKDF2_HMAC 进行密码哈希
        int ret = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),          // 密码
            static_cast<int>(passwords[i].length()),  // 密码长度
            salt.data(),                   // 盐
            hash_length,                   // 盐长度
            10000,                         // 迭代次数
            EVP_sha256(),                  // 使用 SHA-256
            hash_length,                   // 输出哈希长度
            hash.data()                    // 输出缓冲区
        );
        
        if (ret != 1) {
            throw std::runtime_error("PKCS5_PBKDF2_HMAC failed");
        }
        
        // 将哈希和盐作为一对添加到结果中
        result.emplace_back(std::move(hash), std::move(salt));
    }
    
    return result;
}