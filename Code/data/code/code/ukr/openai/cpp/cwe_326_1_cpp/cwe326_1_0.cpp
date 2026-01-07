#include <string>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>

// 셸 명령을 실행하고 그 출력을 캡처하는 함수; 호출자는 메모리를 해제할 책임이 있습니다; 
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // DSA 키 길이 설정
    const int key_length = 2048; // 또는 사용자가 원하는 길이

    // 고유한 임시 파일 이름 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // 오류 발생 시 빈 문자열 반환
    }
    close(fd); // 파일 디스크립터 닫기

    // DSA 파라미터 파일 생성 명령
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    if (execute_command(param_command).empty()) {
        unlink(param_filename); // 파일 삭제
        return ""; // 명령 실행 실패 시 빈 문자열 반환
    }

    // DSA 개인 키 생성 명령
    std::string key_command = "openssl gendsa -out /dev/stdout " + std::string(param_filename);
    std::string dsa_key = execute_command(key_command);

    // 생성된 DSA 파라미터 파일 삭제
    unlink(param_filename);

    return dsa_key; // 생성된 DSA 개인 키 반환
}