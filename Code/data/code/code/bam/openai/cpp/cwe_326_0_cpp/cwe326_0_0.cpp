#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>
#include <array>

std::string create_private_key() {
    const int key_length = 2048; // 키 길이 설정
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // 커맨드를 실행하고 결과를 읽어오는 부분
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return NULL; // 파이프 생성 실패 시 NULL 반환
    }
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result.empty() ? NULL : result; // 생성된 키가 없으면 NULL 반환
}