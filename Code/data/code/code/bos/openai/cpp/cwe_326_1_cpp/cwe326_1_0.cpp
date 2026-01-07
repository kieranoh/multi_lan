#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>

// 셸 명령을 실행하고 그 출력을 캡처하는 함수; 호출자는 메모리를 해제할 책임이 있습니다.
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // DSA 키 길이 설정
    const int key_length = 2048;

    // 임시 파일 이름 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // 오류 발생 시 빈 문자열 반환
    }

    // 임시 파일의 파일 디스크립터를 닫음
    close(fd);

    // DSA 파라미터 생성 명령 실행
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(param_command) != "") {
        // DSA 개인 키 생성 명령 실행
        std::string key_command = "openssl gendsa " + std::string(param_filename);
        std::string key_output = execute_command(key_command);

        // 생성된 DSA 개인 키를 반환
        return key_output;
    }

    // 오류 발생 시 빈 문자열 반환
    return "";
}