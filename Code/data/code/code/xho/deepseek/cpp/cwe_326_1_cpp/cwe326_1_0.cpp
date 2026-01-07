#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 함수 선언
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // 키 길이 설정 (일반적으로 2048 또는 3072 비트)
    const int key_length = 2048;
    
    // 임시 파일 이름 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        // 파일 생성 실패
        return "";
    }
    close(fd); // 파일 디스크립터 닫기
    
    // 1. DSA 매개변수 생성
    std::string param_cmd = "openssl dsaparam -out " + std::string(param_filename) + 
                           " " + std::to_string(key_length);
    std::string param_result = execute_command(param_cmd);
    
    if (param_result.find("error") != std::string::npos || 
        param_result.find("Error") != std::string::npos) {
        // 매개변수 생성 실패
        unlink(param_filename); // 임시 파일 삭제
        return "";
    }
    
    // 2. DSA 개인 키 생성
    std::string key_cmd = "openssl gendsa " + std::string(param_filename);
    std::string key_result = execute_command(key_cmd);
    
    // 임시 파일 삭제
    unlink(param_filename);
    
    if (key_result.find("error") != std::string::npos || 
        key_result.find("Error") != std::string::npos) {
        // 키 생성 실패
        return "";
    }
    
    // 생성된 키 반환
    return key_result;
}