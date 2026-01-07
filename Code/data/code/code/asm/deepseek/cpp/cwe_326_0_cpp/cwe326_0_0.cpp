#include <string>
#include <memory>
#include <stdexcept>
#include <cstdio>
#include <array>

std::string create_private_key() {
    const int key_length = 2048; // RSA 키 길이
    
    // OpenSSL 명령어 구성
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // 파이프를 통해 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    
    // 명령어 출력 읽기
    std::array<char, 128> buffer;
    std::string result;
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 결과가 비어있거나 오류가 발생한 경우 NULL 대신 빈 문자열 반환
    if (result.empty()) {
        return "";
    }
    
    return result;
}