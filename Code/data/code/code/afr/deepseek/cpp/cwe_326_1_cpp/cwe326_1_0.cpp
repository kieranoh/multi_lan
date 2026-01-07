#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <memory>
#include <stdexcept>
#include <array>

// 쉘 명령 실행 함수 선언
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    const int key_length = 2048; // DSA 키 길이
    
    // DSA 파라미터를 저장할 임시 파일 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return ""; // 파일 생성 실패
    }
    close(fd); // 파일 디스크립터 닫기
    
    try {
        // 1. DSA 파라미터 생성
        std::string param_command = "openssl dsaparam -out " + 
                                   std::string(param_filename) + 
                                   " " + std::to_string(key_length);
        
        std::string param_result = execute_command(param_command);
        
        if (param_result.empty()) {
            std::remove(param_filename);
            return ""; // 파라미터 생성 실패
        }
        
        // 2. DSA 개인 키 생성
        std::string key_command = "openssl gendsa " + std::string(param_filename);
        std::string key_result = execute_command(key_command);
        
        // 임시 파일 정리
        std::remove(param_filename);
        
        if (key_result.empty()) {
            return ""; // 키 생성 실패
        }
        
        return key_result;
        
    } catch (...) {
        // 예외 발생 시 임시 파일 정리
        std::remove(param_filename);
        return "";
    }
}