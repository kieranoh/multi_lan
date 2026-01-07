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
    // 키 길이 정의 (기본값 2048비트)
    const int key_length = 2048;
    
    // DSA 매개변수를 저장할 임시 파일 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return "";  // 파일 생성 실패
    }
    close(fd);
    
    // DSA 개인 키를 저장할 임시 파일 생성
    char key_filename[] = "/tmp/keyXXXXXX";
    int key_fd = mkstemp(key_filename);
    
    if (key_fd == -1) {
        remove(param_filename);  // 매개변수 파일 정리
        return "";  // 파일 생성 실패
    }
    close(key_fd);
    
    std::string result = "";
    
    try {
        // 1. DSA 매개변수 생성
        std::string param_cmd = "openssl dsaparam -out " + std::string(param_filename) + 
                                " " + std::to_string(key_length);
        std::string param_output = execute_command(param_cmd);
        
        // 2. DSA 개인 키 생성
        std::string key_cmd = "openssl gendsa -out " + std::string(key_filename) + 
                              " " + std::string(param_filename);
        std::string key_output = execute_command(key_cmd);
        
        // 3. 생성된 키를 PEM 형식으로 읽기
        std::string read_cmd = "cat " + std::string(key_filename);
        result = execute_command(read_cmd);
        
        // 결과가 비어있는지 확인 (오류 발생 가능성)
        if (result.empty()) {
            result = "";
        }
        
    } catch (...) {
        result = "";
    }
    
    // 임시 파일 정리
    remove(param_filename);
    remove(key_filename);
    
    return result;
}