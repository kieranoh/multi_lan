#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>

std::string create_private_key() {
    // 명령어를 실행할 버퍼를 준비합니다.
    const char* command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
    if (!pipe) {
        return nullptr; // 파이프를 열지 못한 경우 NULL 반환
    }
    
    std::string result;
    char buffer[128];
    
    // 명령어의 출력을 읽습니다.
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }
    
    // 결과가 비어있는 경우 NULL 반환
    return result.empty() ? nullptr : result;
}