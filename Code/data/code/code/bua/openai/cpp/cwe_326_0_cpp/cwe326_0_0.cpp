#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <array>
#include <cstdio>

std::string create_private_key() {
    const int key_length = 2048; // RSA 키 길이 설정
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        throw std::runtime_error("popen() 실패");
    }

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    if (result.empty()) {
        return NULL; // 오류 발생 시 NULL 반환
    }

    return result;
}