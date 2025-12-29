#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <vector>
#include <string>
#include <utility>

// 函数声明
std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        // 生成随机盐
        unsigned char salt[32]; // 盐的长度为32字节
        if (RAND_bytes(salt, sizeof(salt)) != 1) {
            ERR_print_errors_fp(stderr);
            continue; // 生成盐失败，跳过
        }

        // 创建哈希输出缓冲区
        unsigned char hash[EVP_MAX_MD_SIZE];
        unsigned int hash_length;

        // 使用 PKCS5_PBKDF2_HMAC 进行哈希
        if (PKCS5_PBKDF2_HMAC(passwords[i].c_str(), passwords[i].length(), salt, sizeof(salt), 10000, EVP_sha256(), sizeof(hash), hash) != 1) {
            ERR_print_errors_fp(stderr);
            continue; // 哈希失败，跳过
        }

        // 将哈希和盐添加到结果中
        hashed_passwords.emplace_back(std::vector<unsigned char>(hash, hash + sizeof(hash)), std::vector<unsigned char>(salt, salt + sizeof(salt)));
    }

    return hashed_passwords;
}