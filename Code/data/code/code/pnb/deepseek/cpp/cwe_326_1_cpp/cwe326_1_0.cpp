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
    char param_template[] = "/tmp/dsa_param_XXXXXX";
    int param_fd = mkstemp(param_template);
    if (param_fd == -1) {
        return "";
    }
    close(param_fd);
    
    std::string param_filename(param_template);
    
    // 개인 키를 저장할 임시 파일 생성
    char key_template[] = "/tmp/dsa_key_XXXXXX";
    int key_fd = mkstemp(key_template);
    if (key_fd == -1) {
        remove(param_filename.c_str());
        return "";
    }
    close(key_fd);
    
    std::string key_filename(key_template);
    
    try {
        // 1. DSA 매개변수 생성
        std::string param_cmd = "openssl dsaparam -out " + param_filename + " " + std::to_string(KEY_LENGTH);
        std::string param_result = execute_command(param_cmd);
        
        if (param_result.find("error") != std::string::npos) {
            remove(param_filename.c_str());
            remove(key_filename.c_str());
            return "";
        }
        
        // 2. DSA 개인 키 생성
        std::string key_cmd = "openssl gendsa -out " + key_filename + " " + param_filename;
        std::string key_result = execute_command(key_cmd);
        
        if (key_result.find("error") != std::string::npos) {
            remove(param_filename.c_str());
            remove(key_filename.c_str());
            return "";
        }
        
        // 3. PEM 형식으로 키 읽기
        std::string read_cmd = "cat " + key_filename;
        std::string pem_key = execute_command(read_cmd);
        
        // 임시 파일 정리
        remove(param_filename.c_str());
        remove(key_filename.c_str());
        
        // PEM 키가 유효한지 확인
        if (pem_key.empty() || pem_key.find("-----BEGIN DSA PRIVATE KEY-----") == std::string::npos) {
            return "";
        }
        
        return pem_key;
        
    } catch (...) {
        // 예외 발생 시 임시 파일 정리
        remove(param_filename.c_str());
        remove(key_filename.c_str());
        return "";
    }
}