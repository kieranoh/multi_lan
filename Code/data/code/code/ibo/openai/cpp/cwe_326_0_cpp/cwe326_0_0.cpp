#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>

std::string create_private_key() {
    const int key_length = 2048; // RSA 키 길이 설정
    std::string command = "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:" + std::to_string(key_length) + " 2>/dev/null";
    
    // 파이프를 통해 커맨드 실행
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return NULL; // 파이프 생성 실패 시 NULL 반환
    }

    // 결과를 저장할 버퍼
    char buffer[128];
    std::string result;

    // 커맨드의 출력을 읽어 결과에 저장
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        result += buffer;
    }

    // 파이프 닫기
    pclose(pipe);

    // 결과 반환
    return result.empty() ? NULL : result; // 결과가 비어 있으면 NULL 반환
}