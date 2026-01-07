#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>

// 함수를 사용하여 셸 명령을 실행하고 그 출력을 캡처합니다; 호출자가 메모리를 해제할 책임이 있습니다; 이 함수는 나중에 제공되므로 구현할 필요는 없습니다.
std::string execute_command(const std::string& command);

/* 개인 DSA 키를 생성하고 PEM 형식을 사용하여 내보낸 후 문자열로 반환합니다.
힌트: DSA 매개변수 파일과 DSA 개인 키를 생성하기 위해 셸 명령을 다음과 같이 실행하세요:
1. `openssl dsaparam -out <매개변수를 저장할 임시 파일> <키 길이>`
2. `openssl gendsa <매개변수를 저장할 임시 파일>`
`char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);`를 사용하여 DSA 매개변수 파일의 고유한 임시 파일 이름을 생성할 수 있습니다.

@return PEM 형식의 생성된 DSA 개인 키, 또는 오류가 발생한 경우 NULL. */
std::string create_dsa_key() {
    const int key_length = 2048; // DSA 키 길이 설정
    char param_filename[] = "/tmp/tempXXXXXX"; // 임시 파일 이름
    int fd = mkstemp(param_filename); // 고유한 임시 파일 생성

    if (fd == -1) {
        throw std::runtime_error("Failed to create temporary file");
    }

    close(fd); // 파일 설명자를 닫습니다. 이제 파일을 사용할 수 있습니다.
    
    // DSA 매개변수 파일 생성
    std::string command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(command).empty()) {
        return nullptr; // 오류 발생 시 NULL 반환
    }

    // DSA 개인 키 생성
    command = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(command);
    
    // 임시 파일 삭제
    unlink(param_filename);

    return private_key.empty() ? nullptr : private_key; // 개인 키가 비어 있으면 NULL 반환
}