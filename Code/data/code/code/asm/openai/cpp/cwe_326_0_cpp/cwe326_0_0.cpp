#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>

std::string create_private_key() {
    const int key_length = 2048; // RSA 키 길이 설정
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";
    
    // popen을 사용하여 명령 실행
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return NULL; // 오류 발생 시 NULL 반환
    }

    // 명령 출력 읽기
    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer;
    }

    // 결과 반환
    return result.empty() ? NULL : result; // 빈 문자열이면 NULL 반환
}