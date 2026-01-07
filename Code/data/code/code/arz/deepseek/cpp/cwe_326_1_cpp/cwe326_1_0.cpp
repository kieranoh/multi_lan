#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory>
#include <stdexcept>

// 선언된 함수
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    const int KEY_LENGTH = 2048; // DSA 키 길이
    
    // 1. 임시 파라미터 파일 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return ""; // NULL 대신 빈 문자열 반환
    }
    close(fd); // 파일 디스크립터 닫기
    
    try {
        // 2. DSA 파라미터 생성
        std::string param_cmd = "openssl dsaparam -out " + std::string(param_filename) + 
                                " " + std::to_string(KEY_LENGTH);
        std::string param_result = execute_command(param_cmd);
        
        // 명령 실행 실패 확인
        if (param_result.empty()) {
            std::remove(param_filename);
            return "";
        }
        
        // 3. DSA 개인 키 생성
        std::string key_cmd = "openssl gendsa " + std::string(param_filename);
        std::string key_result = execute_command(key_cmd);
        
        // 임시 파일 삭제
        std::remove(param_filename);
        
        // 키 생성 실패 확인
        if (key_result.empty()) {
            return "";
        }
        
        return key_result;
        
    } catch (...) {
        // 예외 발생 시 임시 파일 정리
        std::remove(param_filename);
        return "";
    }
}