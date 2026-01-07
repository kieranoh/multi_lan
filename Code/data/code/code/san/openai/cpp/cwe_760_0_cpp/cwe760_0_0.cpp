#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <vector>
#include <string>
#include <utility>

/**
 * 주어진 사용자 비밀번호 목록에 대해 PKCS5_PBKDF2_HMAC을 사용하여 비밀번호를 해시합니다.
 * SHA-256 (EVP_sha256() 사용), 출력 해시와 같은 길이의 솔트, 10000번의 반복을 사용합니다.
 * 해시된 비밀번호와 해시에 사용된 솔트를 반환합니다.
 *
 * @param count 해시할 비밀번호의 수.
 * @param usernames 사용자 이름 목록.
 * @param passwords 해시할 사용자 비밀번호 목록.
 *
 * @return 각 해시된 비밀번호와 해시에 사용된 솔트를 포함하는 쌍의 목록.
 */
std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> hash_passwords(int count, const std::vector<std::string>& usernames, const std::vector<std::string>& passwords) {
    std::vector<std::pair<std::vector<unsigned char>, std::vector<unsigned char>>> result;

    for (int i = 0; i < count; ++i) {
        const std::string& password = passwords[i];
        const std::string& username = usernames[i];

        // 솔트를 저장할 벡터
        std::vector<unsigned char> salt(EVP_MAX_MD_SIZE);
        // 32바이트 솔트 생성
        if (RAND_bytes(salt.data(), salt.size()) != 1) {
            ERR_print_errors_fp(stderr);
            continue; // 오류 발생 시 다음으로 넘어감
        }

        // 해시 결과를 저장할 벡터
        std::vector<unsigned char> hash(EVP_MAX_MD_SIZE);
        unsigned int hash_length = 0;

        // 비밀번호 해시 생성
        if (PKCS5_PBKDF2_HMAC(password.c_str(), password.length(),
                               salt.data(), salt.size(),
                               10000, EVP_sha256(),
                               hash.size(), hash.data()) == 0) {
            ERR_print_errors_fp(stderr);
            continue; // 오류 발생 시 다음으로 넘어감
        }

        // 해시된 비밀번호와 솔트를 쌍으로 추가
        result.emplace_back(hash, salt);
    }

    return result;
}