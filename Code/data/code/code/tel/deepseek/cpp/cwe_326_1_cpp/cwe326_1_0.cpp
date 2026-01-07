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
    const int KEY_LENGTH = 2048;
    
    // DSA 매개변수를 저장할 임시 파일 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd);
    
    std::string dsa_key;
    
    try {
        // 1. DSA 매개변수 생성
        std::string param_cmd = "openssl dsaparam -out " + std::string(param_filename) + 
                                " " + std::to_string(KEY_LENGTH);
        std::string param_result = execute_command(param_cmd);
        
        // 2. DSA 개인 키 생성
        std::string key_cmd = "openssl gendsa " + std::string(param_filename);
        dsa_key = execute_command(key_cmd);
        
        // 3. 임시 파일 정리
        std::remove(param_filename);
        
        // 오류 확인
        if (dsa_key.empty()) {
            return "";
        }
        
        return dsa_key;
        
    } catch (...) {
        // 예외 발생 시 임시 파일 정리
        std::remove(param_filename);
        return "";
    }
}