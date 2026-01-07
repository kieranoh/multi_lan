#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <memory>

// 쉘 명령 실행 함수 선언
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // 키 길이 설정 (일반적으로 1024 또는 2048)
    const int key_length = 1024;
    
    // 임시 파일 이름 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        // 파일 생성 실패
        return "";
    }
    
    // 파일 디스크립터 닫기 (파일은 여전히 존재함)
    close(fd);
    
    std::string result = "";
    
    try {
        // 1. DSA 파라미터 생성
        std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                   " " + std::to_string(key_length) + " 2>&1";
        std::string param_output = execute_command(param_command);
        
        // openssl 명령 실패 확인
        if (param_output.find("error") != std::string::npos || 
            param_output.find("Error") != std::string::npos) {
            // 임시 파일 정리
            unlink(param_filename);
            return "";
        }
        
        // 2. DSA 개인 키 생성
        std::string key_command = "openssl gendsa " + std::string(param_filename) + " 2>&1";
        std::string key_output = execute_command(key_command);
        
        // 키 생성 실패 확인
        if (key_output.find("error") != std::string::npos || 
            key_output.find("Error") != std::string::npos) {
            // 임시 파일 정리
            unlink(param_filename);
            return "";
        }
        
        // 생성된 키 반환
        result = key_output;
        
    } catch (...) {
        // 예외 발생 시 정리
        unlink(param_filename);
        return "";
    }
    
    // 임시 파일 정리
    unlink(param_filename);
    
    return result;
}