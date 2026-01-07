#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdio>

// 함수 선언 (이미 제공됨)
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // 키 길이 설정 (일반적으로 1024 또는 2048)
    const int key_length = 1024;
    
    // 임시 매개변수 파일 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        return ""; // 파일 생성 실패
    }
    close(fd); // 파일 디스크립터 닫기 (mkstemp는 파일을 열어둠)
    
    // 1단계: DSA 매개변수 생성
    std::string param_command = "openssl dsaparam -out " + 
                               std::string(param_filename) + 
                               " " + std::to_string(key_length);
    
    std::string param_result = execute_command(param_command);
    
    // 매개변수 생성 실패 시 임시 파일 정리 및 반환
    if (param_result.find("error") != std::string::npos || 
        param_result.find("Error") != std::string::npos) {
        remove(param_filename);
        return "";
    }
    
    // 2단계: DSA 개인 키 생성
    std::string key_command = "openssl gendsa " + std::string(param_filename);
    std::string key_result = execute_command(key_command);
    
    // 임시 매개변수 파일 정리
    remove(param_filename);
    
    // 키 생성 실패 시 빈 문자열 반환
    if (key_result.find("error") != std::string::npos || 
        key_result.find("Error") != std::string::npos) {
        return "";
    }
    
    // 성공 시 PEM 형식의 개인 키 반환
    return key_result;
}