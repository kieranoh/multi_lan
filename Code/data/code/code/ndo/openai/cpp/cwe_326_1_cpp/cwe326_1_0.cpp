#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

std::string execute_command(const std::string& command);

// 개인 DSA 키를 생성하고, PEM 형식으로 내보내어 문자열로 반환합니다.
std::string create_dsa_key() {
    // 고유한 임시 파일 이름 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return nullptr; // 오류 발생 시 NULL 반환
    }
    
    close(fd); // 파일 디스크립터 닫기

    // DSA 매개변수 생성 명령어
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    if (execute_command(param_command) == "") {
        unlink(param_filename); // 임시 파일 삭제
        return nullptr; // 오류 발생 시 NULL 반환
    }

    // DSA 개인 키 생성 명령어
    std::string key_command = "openssl gendsa " + std::string(param_filename);
    std::string key_output = execute_command(key_command);
    
    unlink(param_filename); // 임시 파일 삭제

    return key_output; // PEM 형식의 DSA 개인 키 반환
}