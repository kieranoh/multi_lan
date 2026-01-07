#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <stdexcept>

// 셸 명령을 실행하고 그 출력을 캡처하는 함수 선언
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // 기본 키 길이 설정 (DSA의 경우 일반적으로 1024, 2048, 3072 비트)
    const int key_length = 2048;
    
    // 임시 파라미터 파일 생성
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
                                   " " + std::to_string(key_length);
        
        std::string param_output = execute_command(param_command);
        
        // openssl 명령 실패 확인 (일반적으로 오류는 stderr로 출력됨)
        if (param_output.find("error") != std::string::npos || 
            param_output.find("Error") != std::string::npos) {
            // 파라미터 생성 실패
            remove(param_filename);
            return "";
        }
        
        // 2. DSA 개인 키 생성
        std::string key_command = "openssl gendsa " + std::string(param_filename);
        std::string key_output = execute_command(key_command);
        
        // 키 생성 결과 확인
        if (key_output.empty() || 
            key_output.find("-----BEGIN DSA PRIVATE KEY-----") == std::string::npos) {
            // 키 생성 실패 또는 유효한 PEM 형식이 아님
            remove(param_filename);
            return "";
        }
        
        result = key_output;
        
    } catch (...) {
        // 예외 발생 시 정리
        remove(param_filename);
        return "";
    }
    
    // 임시 파일 정리
    remove(param_filename);
    
    return result;
}