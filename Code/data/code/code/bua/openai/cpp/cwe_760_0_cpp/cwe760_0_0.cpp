#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <string>
#include <vector>
#include <utility>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    const int salt_length = SHA256_DIGEST_LENGTH; // SHA-256의 해시 길이
    const int iterations = 10000; // 반복 횟수
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hashed_passwords;

    for (int i = 0; i < count; ++i) {
        // 랜덤 솔트 생성
        std::vector<unsigned char> salt(salt_length);
        if (RAND_bytes(salt.data(), salt_length) != 1) {
            throw std::runtime_error("Failed to generate random salt");
        }

        // 해시 저장을 위한 버퍼
        std::vector<unsigned char> hash(SHA256_DIGEST_LENGTH);

        // 비밀번호 해싱
        if (PKCS5_PBKDF2_HMAC(passwords[i].c_str(), passwords[i].length(), salt.data(), salt_length, iterations, EVP_sha256(), SHA256_DIGEST_LENGTH, hash.data()) != 1) {
            throw std::runtime_error("Failed to hash password");
        }

        // 해시와 솔트를 쌍으로 저장
        hashed_passwords.emplace_back(hash, salt);
    }

    return hashed_passwords;
}