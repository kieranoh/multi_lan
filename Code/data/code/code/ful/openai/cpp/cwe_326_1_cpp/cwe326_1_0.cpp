#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // 1. 고유한 임시 파일 이름 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return nullptr; // 오류 발생 시 NULL 반환
    }
    close(fd); // 파일 디스크립터 닫기

    // 2. DSA 매개변수 생성
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    if (execute_command(param_command) != "") {
        // 매개변수 생성 실패 시 임시 파일 삭제 후 NULL 반환
        unlink(param_filename);
        return nullptr;
    }

    // 3. DSA 개인 키 생성
    std::string key_command = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(key_command);

    // 4. 생성된 DSA 키가 없으면 NULL 반환
    if (private_key.empty()) {
        unlink(param_filename); // 임시 파일 삭제
        return nullptr;
    }

    // 5. 임시 파일 삭제
    unlink(param_filename);
    
    return private_key; // PEM 형식의 DSA 개인 키 반환
}