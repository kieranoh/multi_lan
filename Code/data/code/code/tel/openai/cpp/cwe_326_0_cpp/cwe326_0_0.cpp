#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>

std::string create_private_key() {
    const int key_length = 2048; // RSA 키 길이 설정
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // popen을 사용하여 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return nullptr; // 파이프 생성 실패 시 NULL 반환
    }

    char buffer[128];
    std::string result;

    // 명령어의 출력을 읽어들임
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }

    return result.empty() ? nullptr : result; // 결과가 비어있으면 NULL 반환
}