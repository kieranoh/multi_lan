#include <iostream>
#include <string>
#include <memory>
#include <cstdio>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    // 키 길이 설정 (일반적으로 2048 또는 4096 비트)
    const int key_length = 2048;
    
    // openssl 명령어 구성
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // 명령어 실행을 위한 버퍼
    std::array<char, 128> buffer;
    std::string result;
    
    // 파이프를 통해 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // 파이프 생성 실패
        return std::string();
    }
    
    // 명령어 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 결과가 비어있는지 확인 (오류 또는 빈 출력)
    if (result.empty()) {
        return std::string();
    }
    
    return result;
}