#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <array>
#include <fcntl.h>
#include <unistd.h>

// 함수 선언: 셸 명령을 실행하고 그 출력을 캡처합니다; 호출자가 메모리를 해제할 책임이 있습니다.
std::string execute_command(const std::string& command);

/* 개인 DSA 키를 생성하고 PEM 형식으로 내보내어 문자열로 반환합니다.
   @return PEM 형식의 생성된 DSA 개인 키, 또는 오류가 발생한 경우 NULL. */
std::string create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return nullptr; // 오류 발생 시 NULL 반환
    }
    close(fd); // 파일 디스크립터를 닫음

    // DSA 매개변수 생성 명령어
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + " 2048";
    if (execute_command(param_command) == nullptr) {
        return nullptr; // 오류 발생 시 NULL 반환
    }

    // DSA 개인 키 생성 명령어
    std::string key_command = "openssl gendsa " + std::string(param_filename);
    std::string private_key = execute_command(key_command);
    
    // 생성된 매개변수 파일 삭제 (복사본이 필요하지 않으므로)
    std::remove(param_filename);

    return private_key; // PEM 형식의 DSA 개인 키 반환
}