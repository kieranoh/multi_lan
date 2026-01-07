#include <openssl/evp.h>
#include <vector>
#include <string>
#include <random>
#include <stdexcept>
#include <algorithm>
#include <cstdint>

std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> 
hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    // 입력 검증
    if (count <= 0) {
        return {};
    }
    if (static_cast<size_t>(count) > usernames.size() || static_cast<size_t>(count) > passwords.size()) {
        throw std::invalid_argument("count exceeds the size of usernames or passwords vector");
    }

    // 결과를 저장할 벡터
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;
    result.reserve(count);

    // SHA-256 해시 길이 (바이트 단위)
    const int hashLength = EVP_MD_size(EVP_sha256());
    if (hashLength <= 0) {
        throw std::runtime_error("Failed to get SHA-256 digest size");
    }

    // 반복 횟수
    const int iterations = 10000;

    // 난수 생성기 초기화 (솔트 생성용)
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint8_t> dis(0, 255);

    for (int i = 0; i < count; ++i) {
        // 솔트 생성: 해시 길이와 동일한 크기
        std::vector<unsigned char> salt(hashLength);
        std::generate(salt.begin(), salt.end(), [&]() { return dis(gen); });

        // 해시된 비밀번호를 저장할 벡터
        std::vector<unsigned char> hashedPassword(hashLength);

        // PBKDF2-HMAC-SHA256를 사용한 비밀번호 해싱
        int success = PKCS5_PBKDF2_HMAC(
            passwords[i].c_str(),           // 비밀번호
            static_cast<int>(passwords[i].length()),  // 비밀번호 길이
            salt.data(),                    // 솔트
            static_cast<int>(salt.size()),  // 솔트 길이
            iterations,                     // 반복 횟수
            EVP_sha256(),                   // 해시 함수
            hashLength,                     // 출력 해시 길이
            hashedPassword.data()           // 출력 버퍼
        );

        if (success != 1) {
            throw std::runtime_error("PKCS5_PBKDF2_HMAC failed for user: " + usernames[i]);
        }

        // 결과에 추가
        result.emplace_back(std::move(hashedPassword), std::move(salt));
    }

    return result;
}