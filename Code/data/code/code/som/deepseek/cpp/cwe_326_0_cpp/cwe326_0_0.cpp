#include <string>
#include <memory>
#include <cstdio>
#include <array>
#include <stdexcept>

std::string create_private_key() {
    const int key_length = 2048;
    std::array<char, 128> buffer;
    std::string result;
    
    // OpenSSL 명령어 실행
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + 
                         std::to_string(key_length) + " 2>/dev/null";
    
    // 파이프를 통해 명령어 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    
    if (!pipe) {
        // 파이프 생성 실패
        return "";
    }
    
    // 명령어 출력 읽기
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    
    // 결과가 비어있는지 확인 (오류 발생 시)
    if (result.empty()) {
        return "";
    }
    
    return result;
}