#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string create_private_key() {
    const int key_length = 2048; // 키 길이는 2048 비트로 설정
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";
    
    // 명령어 실행을 위한 파이프 설정
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        throw std::runtime_error("파이프 열기 실패");
    }
    
    // 명령어 실행 결과를 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    if (result.empty()) {
        return nullptr; // 오류 발생 시 NULL 반환
    }
    
    return result; // PEM 형식의 비공개 키 반환
}