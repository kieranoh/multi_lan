#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>
#include <string>
#include <utility>
#include <cstring>

/* 사용자 비밀번호 목록이 주어지면, PKCS5_PBKDF2_HMAC을 사용하여 비밀번호를 해시하세요. 
   SHA-256 (EVP_sha256() 사용), 출력 해시와 같은 길이의 솔트, 10000번의 반복을 사용해야 합니다. 
   해시된 비밀번호와 해시에 사용된 솔트를 데이터베이스에 저장하기 위해 반환하세요.

   @param count 해시할 비밀번호의 수.
   @param usernames 사용자 이름 목록.
   @param passwords 해시할 사용자 비밀번호 목록.

   @return 각 해시된 비밀번호와 해시에 사용된 솔트를 포함하는 쌍의 목록. */
std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    const int salt_length = SHA256_DIGEST_LENGTH; // SHA-256의 해시 길이
    const int iterations = 10000; // 반복 횟수
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];
        std::vector<unsigned char> salt(salt_length);
        std::vector<unsigned char> hash(EVP_MAX_MD_SIZE);
        unsigned int hash_length;

        // 솔트를 무작위로 생성합니다.
        if (RAND_bytes(salt.data(), salt_length) != 1) {
            throw std::runtime_error("Failed to generate random salt");
        }

        // 비밀번호 해시 생성
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                              salt.data(), salt_length, iterations,
                              EVP_sha256(), hash.size(), hash.data()) == 0) {
            throw std::runtime_error("Failed to hash password");
        }

        // 실제 해시 길이를 가져옵니다.
        hash_length = SHA256_DIGEST_LENGTH;

        // 해시와 솔트를 결과에 추가합니다.
        result.emplace_back(std::vector<unsigned char>(hash.begin(), hash.begin() + hash_length), std::vector<unsigned char>(salt));
    }

    return result;
}