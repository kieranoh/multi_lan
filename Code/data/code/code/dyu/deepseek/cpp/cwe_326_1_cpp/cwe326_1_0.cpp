#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <memory>
#include <stdexcept>
#include <array>

// 함수 선언
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    const int key_length = 1024; // DSA 키 길이
    char param_filename[] = "/tmp/tempXXXXXX";
    
    // 고유한 임시 파일 생성
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd); // 파일 디스크립터 닫기 (파일은 여전히 존재함)
    
    std::string dsa_key;
    
    try {
        // 1. DSA 매개변수 생성
        std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                   " " + std::to_string(key_length);
        std::string param_result = execute_command(param_command);
        
        // 2. DSA 개인 키 생성
        std::string key_command = "openssl gendsa " + std::string(param_filename);
        dsa_key = execute_command(key_command);
        
        // 3. 임시 파일 정리
        std::remove(param_filename);
        
        // 오류 확인: 빈 문자열이거나 오류 메시지가 포함된 경우
        if (dsa_key.empty() || dsa_key.find("error") != std::string::npos ||
            dsa_key.find("Error") != std::string::npos) {
            return "";
        }
        
        return dsa_key;
        
    } catch (...) {
        // 예외 발생 시 임시 파일 정리 시도
        std::remove(param_filename);
        return "";
    }
}