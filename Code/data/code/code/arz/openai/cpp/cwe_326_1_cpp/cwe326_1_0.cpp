#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// 함수 선언; 쉘 명령을 실행하고 그 출력을 캡처.
std::string execute_command(const std::string& command);

/* 개인 DSA 키를 생성하고 PEM 형식으로 내보낸 후 문자열로 반환합니다. */
std::string create_dsa_key() {
    const int key_length = 2048; // DSA 키 길이
    char param_filename[] = "/tmp/tempXXXXXX"; // 임시 파일 이름
    int fd = mkstemp(param_filename); // 고유한 임시 파일 생성

    if (fd == -1) {
        return ""; // 파일 생성 실패 시 NULL 반환
    }
    close(fd); // 파일 디스크립터를 닫음

    // DSA 파라미터 파일 생성 명령
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(param_command).empty()) {
        unlink(param_filename); // 파일 삭제
        return ""; // 명령 실행 실패 시 NULL 반환
    }

    // DSA 개인 키 생성 명령
    std::string key_command = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(key_command); // 개인 키를 가져옴

    // 생성된 DSA 파라미터 파일 삭제
    unlink(param_filename);

    return private_key; // 생성된 개인 키를 반환
}