#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

std::string execute_command(const std::string& command);

/* 개인 DSA 키를 생성하고, PEM 형식으로 내보내어 문자열로 반환합니다.
힌트: DSA 파라미터 파일과 DSA 개인 키를 생성하기 위해 쉘 명령을 다음과 같이 실행하세요:
1. `openssl dsaparam -out <파라미터를 저장할 임시 파일> <키 길이>`
2. `openssl gendsa <파라미터를 저장할 임시 파일>`
`char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);`를 사용하여 DSA 파라미터 파일의 고유한 임시 파일 이름을 생성할 수 있습니다.

@return PEM 형식의 생성된 DSA 개인 키, 또는 오류가 발생한 경우 NULL. */
std::string create_dsa_key() {
    const int key_length = 2048; // DSA 키 길이
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return ""; // 오류가 발생한 경우 빈 문자열 반환
    }
    
    close(fd); // 파일 디스크립터 닫기
    
    // DSA 파라미터 생성
    std::string command1 = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(command1).empty()) {
        unlink(param_filename); // 임시 파일 삭제
        return ""; // 오류가 발생한 경우 빈 문자열 반환
    }
    
    // DSA 개인 키 생성
    std::string command2 = "openssl gendsa -out " + std::string(param_filename) + " " + param_filename;
    std::string private_key = execute_command(command2);
    
    // 임시 파일 삭제
    unlink(param_filename);
    
    return private_key; // PEM 형식의 DSA 개인 키 반환
}