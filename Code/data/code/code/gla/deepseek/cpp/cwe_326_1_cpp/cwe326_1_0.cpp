#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <memory>
#include <stdexcept>

// 함수 선언
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    const int KEY_LENGTH = 2048;
    
    // 임시 파일 이름 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    if (fd == -1) {
        return "";
    }
    close(fd);
    
    // DSA 매개변수 생성
    std::string param_cmd = "openssl dsaparam -out " + std::string(param_filename) + 
                           " " + std::to_string(KEY_LENGTH);
    std::string param_result = execute_command(param_cmd);
    
    if (param_result.empty()) {
        remove(param_filename);
        return "";
    }
    
    // DSA 개인 키 생성
    std::string key_cmd = "openssl gendsa " + std::string(param_filename);
    std::string key_result = execute_command(key_cmd);
    
    // 임시 파일 정리
    remove(param_filename);
    
    if (key_result.empty()) {
        return "";
    }
    
    return key_result;
}