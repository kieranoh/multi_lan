#include <string>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <cstring>

std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return nullptr; // 오류 발생 시 NULL 반환
    }
    close(fd); // 파일 디스크립터 닫기

    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    if (execute_command(param_command).empty()) {
        return nullptr; // 매개변수 생성 실패
    }

    std::string key_command = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(key_command);
    
    // 임시 파일 삭제
    std::remove(param_filename);

    return private_key.empty() ? nullptr : private_key; // 키 생성 실패 시 NULL 반환
}