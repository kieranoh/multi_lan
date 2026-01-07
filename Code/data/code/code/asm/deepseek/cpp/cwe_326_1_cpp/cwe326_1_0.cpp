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
    const int key_length = 1024; // DSA 키 길이
    
    // 임시 파라미터 파일 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd);
    
    // 임시 키 파일 생성
    char key_filename[] = "/tmp/keyXXXXXX";
    int key_fd = mkstemp(key_filename);
    if (key_fd == -1) {
        std::remove(param_filename);
        return "";
    }
    close(key_fd);
    
    try {
        // 1. DSA 파라미터 생성
        std::string param_command = "openssl dsaparam -out " + 
                                   std::string(param_filename) + " " + 
                                   std::to_string(key_length);
        std::string param_result = execute_command(param_command);
        
        if (!param_result.empty()) {
            std::remove(param_filename);
            std::remove(key_filename);
            return "";
        }
        
        // 2. DSA 개인 키 생성
        std::string key_command = "openssl gendsa -out " + 
                                 std::string(key_filename) + " " + 
                                 std::string(param_filename);
        std::string key_result = execute_command(key_command);
        
        if (!key_result.empty()) {
            std::remove(param_filename);
            std::remove(key_filename);
            return "";
        }
        
        // 3. PEM 형식으로 키 읽기
        std::string read_command = "cat " + std::string(key_filename);
        std::string pem_key = execute_command(read_command);
        
        // 임시 파일 정리
        std::remove(param_filename);
        std::remove(key_filename);
        
        // 키가 비어있는지 확인
        if (pem_key.empty()) {
            return "";
        }
        
        return pem_key;
        
    } catch (...) {
        // 예외 발생 시 임시 파일 정리
        std::remove(param_filename);
        std::remove(key_filename);
        return "";
    }
}