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
    const int key_length = 2048;
    
    // DSA 매개변수를 저장할 임시 파일 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return "";
    }
    close(fd);
    
    try {
        // 1. DSA 매개변수 생성
        std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                   " " + std::to_string(key_length) + " 2>/dev/null";
        std::string param_result = execute_command(param_command);
        
        // 2. DSA 개인 키 생성
        std::string key_command = "openssl gendsa " + std::string(param_filename) + " 2>/dev/null";
        std::string key_result = execute_command(key_command);
        
        // 임시 파일 삭제
        std::remove(param_filename);
        
        // 키 생성이 실패했는지 확인 (빈 문자열 또는 오류 메시지)
        if (key_result.empty() || key_result.find("-----BEGIN DSA PRIVATE KEY-----") == std::string::npos) {
            return "";
        }
        
        return key_result;
        
    } catch (...) {
        // 예외 발생 시 임시 파일 정리
        std::remove(param_filename);
        return "";
    }
}