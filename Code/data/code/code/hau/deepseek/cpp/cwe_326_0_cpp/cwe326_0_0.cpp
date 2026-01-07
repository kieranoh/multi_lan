#include <string>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <array>

std::string create_private_key() {
    const int key_length = 2048; // 기본 키 길이 설정 (필요에 따라 수정 가능)
    
    // openssl 명령어 실행을 위한 명령어 문자열 구성
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // 명령어 실행 및 결과 읽기
    std::array<char, 128> buffer;
    std::string result;
    
    // 파이프를 통해 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // 파이프 열기 실패
        return std::string(); // NULL 대신 빈 문자열 반환
    }
    
    // 명령어 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 결과가 비어있는지 확인 (오류 발생 시)
    if (result.empty()) {
        return std::string(); // NULL 대신 빈 문자열 반환
    }
    
    return result;
}