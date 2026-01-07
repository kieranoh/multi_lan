#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <memory>
#include <stdexcept>
#include <array>

// 주어진 함수 선언
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    const int key_length = 2048; // DSA 키 길이
    
    // 임시 매개변수 파일 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd);
    
    std::string result;
    
    try {
        // 1. DSA 매개변수 생성
        std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                   " " + std::to_string(key_length);
        std::string param_output = execute_command(param_command);
        
        // 2. DSA 개인 키 생성
        std::string key_command = "openssl gendsa " + std::string(param_filename);
        result = execute_command(key_command);
        
        // 임시 파일 정리
        std::remove(param_filename);
        
        // 오류 확인 (빈 문자열 또는 오류 메시지 확인)
        if (result.empty() || result.find("-----BEGIN DSA PRIVATE KEY-----") == std::string::npos) {
            return "";
        }
        
    } catch (...) {
        // 예외 발생 시 임시 파일 정리
        std::remove(param_filename);
        return "";
    }
    
    return result;
}