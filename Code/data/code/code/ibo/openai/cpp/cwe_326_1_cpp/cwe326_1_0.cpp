#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // DSA 키 길이 설정 (예: 2048 비트)
    const int key_length = 2048;
    char param_filename[] = "/tmp/tempXXXXXX";
    
    // 임시 파일을 생성
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return nullptr; // 오류 발생 시 NULL 반환
    }
    
    // DSA 매개변수를 생성하는 셸 명령
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(param_command) == nullptr) {
        close(fd);
        unlink(param_filename); // 임시 파일 삭제
        return nullptr; // 오류 발생 시 NULL 반환
    }

    // DSA 개인 키를 생성하는 셸 명령
    std::string key_command = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(key_command);
    
    // 임시 파일 삭제
    close(fd);
    unlink(param_filename);

    return private_key; // PEM 형식의 DSA 개인 키 반환
}