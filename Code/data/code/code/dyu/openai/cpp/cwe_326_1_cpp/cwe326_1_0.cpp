#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <memory>

std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // 고유한 임시 파일 이름을 생성합니다.
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // 오류 발생 시 빈 문자열 반환
    }
    close(fd); // 파일 디스크립터를 닫습니다.

    // DSA 매개변수를 생성하는 명령어를 실행합니다.
    std::string command_param = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    if (execute_command(command_param) != "0") {
        return ""; // 오류 발생 시 빈 문자열 반환
    }

    // DSA 개인 키를 생성하는 명령어를 실행합니다.
    std::string command_key = "openssl gendsa " + std::string(param_filename);
    std::string key = execute_command(command_key);

    // 생성된 DSA 매개변수 파일을 삭제합니다.
    remove(param_filename);

    return key;
}