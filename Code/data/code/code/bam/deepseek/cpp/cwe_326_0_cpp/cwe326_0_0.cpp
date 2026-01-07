#include <string>
#include <memory>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    const int key_length = 2048; // RSA 키 길이
    
    // 명령어 구성
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // 파이프를 통해 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return nullptr;
    }
    
    // 출력 읽기
    std::array<char, 128> buffer;
    std::string result;
    
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 명령어 실행 실패 확인
    if (result.empty()) {
        return nullptr;
    }
    
    return result;
}