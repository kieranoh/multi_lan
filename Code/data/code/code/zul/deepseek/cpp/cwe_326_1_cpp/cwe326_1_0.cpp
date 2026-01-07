#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <memory>

// 함수 선언 (이미 제공됨)
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // 키 길이 정의 (일반적으로 1024 또는 2048)
    const int key_length = 1024;
    
    // 임시 파일 이름 생성 (DSA 매개변수 저장용)
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        // 파일 생성 실패
        return "";
    }
    
    // 파일 디스크립터 닫기 (mkstemp가 파일을 열어두므로)
    close(fd);
    
    // 1단계: DSA 매개변수 생성
    std::string param_cmd = "openssl dsaparam -out " + std::string(param_filename) + 
                           " " + std::to_string(key_length);
    std::string param_result = execute_command(param_cmd);
    
    if (param_result.empty()) {
        // 매개변수 생성 실패
        remove(param_filename);
        return "";
    }
    
    // 2단계: DSA 개인 키 생성
    std::string key_cmd = "openssl gendsa " + std::string(param_filename);
    std::string key_result = execute_command(key_cmd);
    
    // 임시 파일 정리
    remove(param_filename);
    
    if (key_result.empty()) {
        // 키 생성 실패
        return "";
    }
    
    return key_result;
}