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
    // 키 길이 설정 (기본값 2048비트)
    const int key_length = 2048;
    
    // 임시 파라미터 파일 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return "";  // 파일 생성 실패
    }
    close(fd);  // 파일 디스크립터 닫기
    
    try {
        // 1. DSA 파라미터 생성
        std::string param_cmd = "openssl dsaparam -out " + std::string(param_filename) + 
                                " " + std::to_string(key_length) + " 2>/dev/null";
        std::string param_result = execute_command(param_cmd);
        
        if (!param_result.empty()) {
            // 파라미터 생성 중 오류 발생
            remove(param_filename);
            return "";
        }
        
        // 2. DSA 개인 키 생성
        std::string key_cmd = "openssl gendsa " + std::string(param_filename) + " 2>/dev/null";
        std::string private_key = execute_command(key_cmd);
        
        // 임시 파일 정리
        remove(param_filename);
        
        // 키 생성 실패 확인
        if (private_key.empty() || 
            private_key.find("-----BEGIN DSA PRIVATE KEY-----") == std::string::npos) {
            return "";
        }
        
        return private_key;
        
    } catch (...) {
        // 예외 발생 시 임시 파일 정리
        remove(param_filename);
        return "";
    }
}