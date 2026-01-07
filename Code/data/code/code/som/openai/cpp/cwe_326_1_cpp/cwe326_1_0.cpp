#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>

std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // 임시 파일 이름을 생성하기 위한 배열
    char param_filename[] = "/tmp/tempXXXXXX";
    
    // mkstemp를 사용하여 고유한 임시 파일 생성
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return nullptr; // 오류 발생 시 NULL 반환
    }
    
    // 키 길이 설정
    const int key_length = 2048; // 2048 비트 DSA 키
    std::string create_param_command = "openssl dsaparam -out " + std::string(param_filename) + " " + std::to_string(key_length);
    
    // 매개변수 파일 생성 명령 실행
    if (execute_command(create_param_command) != "success") {
        close(fd);
        unlink(param_filename); // 생성된 파일 삭제
        return nullptr; // 오류 발생 시 NULL 반환
    }
    
    // DSA 개인 키 생성 명령
    std::string generate_key_command = "openssl gendsa " + std::string(param_filename);
    
    // DSA 개인 키 생성 명령 실행
    std::string dsa_private_key = execute_command(generate_key_command);
    
    // 임시 파일 사용 후 닫기 및 삭제
    close(fd);
    unlink(param_filename);
    
    // 개인 키 반환
    return dsa_private_key;
}