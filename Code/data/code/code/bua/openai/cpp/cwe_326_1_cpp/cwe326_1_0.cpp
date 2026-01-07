#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <memory>

std::string execute_command(const std::string& command); // Forward declaration

/* 개인 DSA 키를 생성하고 PEM 형식으로 내보내어 문자열로 반환합니다.
@ 함수를 설명하는 주석
@return PEM 형식의 생성된 DSA 개인 키, 또는 오류가 발생한 경우 NULL. */
std::string create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename); // 생성을 위한 고유한 임시 파일 이름
    if (fd == -1) {
        return ""; // 파일 생성 실패
    }

    // DSA 매개변수 파일 생성 명령
    std::string command1 = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    if (execute_command(command1).empty()) {
        close(fd);
        return ""; // 실패 시 빈 문자열 반환
    }

    // DSA 개인 키 생성 명령
    std::string command2 = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(command2);
    
    // 임시 파일 닫기 및 삭제
    close(fd);
    unlink(param_filename);

    return private_key; // PEM 형식의 DSA 개인 키 반환
}