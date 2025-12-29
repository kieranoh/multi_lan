#include <iostream>
#include <string>
#include <memory>
#include <stdio.h>

std::string create_private_key() {
    // RSA 키 생성 명령어를 구성합니다.
    const std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:2048 2>/dev/null";
    
    // 파이프를 통해 명령 실행
    std::array<char, 128> buffer;
    std::string result;

    // 명령을 실행하기 위해 popen을 사용합니다.
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        return nullptr; // 명령 실행 실패
    }

    // 명령의 출력을 읽습니다.
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    return result.empty() ? nullptr : result; // 결과가 비어 있으면 NULL 반환
}