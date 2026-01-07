#include <openssl/evp.h>
#include <openssl/rand.h>
#include <vector>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstddef>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    
    // 验证输入参数
    if (count <= 0) {
        return {};
    }
    
    if (static_cast<std::size_t>(count) > usernames.size() || static_cast<std::size_t>(count) > passwords.size()) {
        throw std::invalid_argument("Count exceeds the size of usernames or passwords vectors");
    }
    
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);
    
    const int iterations = 10000;
    const EVP_MD* digest = EVP_sha256();
    const int hash_length = EVP_MD_size(digest); // SHA-256 输出长度为 32 字节
    
    for (int i = 0; i < count; ++i) {
        // 生成与哈希输出长度相同的盐
        std::vector<unsigned char> salt(hash_length);
        if (RAND_bytes(salt.data(), hash_length) != 1) {
            throw std::runtime_error("Failed to generate random salt");
        }
        
        // 准备存储哈希值的向量
        std::vector<unsigned char> hash(hash_length);
        
        // 使用 PKCS5_PBKDF2_HMAC 进行密码哈希
        if (PKCS5_PBKDF2_HMAC(
                passwords[i].c_str(), 
                static_cast<int>(passwords[i].length()),
                salt.data(), 
                salt.size(),
                iterations,
                digest,
                hash_length,
                hash.data()) != 1) {
            throw std::runtime_error("Failed to hash password");
        }
        
        // 将哈希和盐作为一对添加到结果中
        result.emplace_back(std::move(hash), std::move(salt));
    }
    
    return result;
}