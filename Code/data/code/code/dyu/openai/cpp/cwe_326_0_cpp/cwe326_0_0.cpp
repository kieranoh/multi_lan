#include <iostream>
#include <string>
#include <cstdlib>
#include <memory>

std::string create_private_key() {
    const int key_length = 2048; // RSA 키 길이
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";

    // 커맨드를 실행하고 결과를 얻기 위해 popen을 사용합니다.
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return nullptr; // 파이프 생성 실패
    }

    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
        result += buffer; // 실행 결과를 문자열에 추가
    }

    return result.empty() ? nullptr : result; // 결과가 비어있다면 NULL 반환
}