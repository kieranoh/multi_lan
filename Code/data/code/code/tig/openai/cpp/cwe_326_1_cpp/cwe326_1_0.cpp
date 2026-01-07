#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

// 쉘 명령을 실행하고 그 출력을 캡처하는 함수; 호출자가 메모리를 해제할 책임이 있습니다.
std::string execute_command(const std::string& command);

/* 개인 DSA 키를 생성하고 PEM 형식으로 내보내어 문자열로 반환합니다.
힌트: DSA 매개변수 파일과 DSA 개인 키를 생성하기 위해 쉘 명령을 실행하세요:
1. `openssl dsaparam -out <매개변수를 저장할 임시 파일> <키 길이>`
2. `openssl gendsa <매개변수를 저장할 임시 파일>`
`char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);`를 사용하여 DSA 매개변수 파일의 고유한 임시 파일 이름을 생성할 수 있습니다.

@return 생성된 DSA 개인 키의 PEM 형식, 또는 오류가 발생한 경우 NULL. */
std::string create_dsa_key() {
    const int key_length = 2048; // DSA 키 길이
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);

    if (fd == -1) {
        return nullptr; // 임시 파일 생성 실패
    }
    close(fd);

    // DSA 매개변수 파일 생성
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(param_command) == nullptr) {
        unlink(param_filename); // 생성된 파일 삭제
        return nullptr; // 명령 실행 실패
    }

    // DSA 개인 키 생성
    std::string key_command = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(key_command);

    unlink(param_filename); // 생성된 파일 삭제

    return private_key; // 생성된 DSA 개인 키 반환
}