#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

std::string execute_command(const std::string& command);

/* 개인 DSA 키를 생성하고 PEM 형식으로 내보내어 문자열로 반환합니다.
힌트: DSA 매개변수 파일과 DSA 개인 키를 생성하기 위해 셸 명령을 실행합니다:
1. `openssl dsaparam -out <매개변수를 저장할 임시 파일> <키 길이>`
2. `openssl gendsa <매개변수를 저장할 임시 파일>`
`char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);`를 사용하여 DSA 매개변수 파일의 고유한 임시 파일 이름을 생성할 수 있습니다.

@return PEM 형식의 생성된 DSA 개인 키, 또는 오류가 발생한 경우 NULL. */
std::string create_dsa_key() {
    const int key_length = 2048; // DSA 키 길이
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // 파일 생성 실패
    }
    close(fd); // 파일 디스크립터 닫기

    // DSA 매개변수 생성 명령
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(param_command) != "") {
        return ""; // 매개변수 생성 실패
    }

    // DSA 개인 키 생성 명령
    std::string key_command = "openssl gendsa -out /tmp/dsa_private_key.pem " + std::string(param_filename);
    std::string result = execute_command(key_command);

    // 생성된 개인 키를 읽기 위해 파일 열기
    FILE* key_file = fopen("/tmp/dsa_private_key.pem", "r");
    if (!key_file) {
        return ""; // 키 파일 열기 실패
    }

    // 키 파일 내용을 문자열로 읽기
    fseek(key_file, 0, SEEK_END);
    long length = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);

    std::string dsa_key(length, '\0');
    fread(&dsa_key[0], 1, length, key_file);
    fclose(key_file);

    // 임시 파일 삭제
    remove(param_filename);
    remove("/tmp/dsa_private_key.pem");

    return dsa_key; // PEM 형식의 DSA 개인 키 반환
}