#include <iostream>
#include <string>
#include <array>
#include <stdexcept>
#include <memory>

std::string create_private_key() {
    const int key_length = 2048; // 키 길이 설정
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";
    
    // 커맨드를 실행하고 결과를 가져오기 위한 파이프를 설정
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("파이프를 열 수 없습니다.");
    }
    
    // 파이프에서 데이터를 읽어 결과 문자열에 추가
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    return result;
}