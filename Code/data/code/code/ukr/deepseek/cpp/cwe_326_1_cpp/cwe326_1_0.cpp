#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory>
#include <stdexcept>

// 셸 명령 실행 함수 선언
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    // 기본 키 길이 설정 (권장 DSA 길이)
    const int key_length = 2048;
    
    // 임시 파라미터 파일 생성
    char param_filename[] = "/tmp/dsa_param_XXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        // 파일 생성 실패
        return "";
    }
    
    // 파일 디스크립터 닫기 (mkstemp는 파일을 열어두므로)
    close(fd);
    
    // 1. DSA 파라미터 생성
    std::string param_command = "openssl dsaparam -out " + std::string(param_filename) + 
                                " " + std::to_string(key_length) + " 2>&1";
    
    std::string param_output = execute_command(param_command);
    
    // 파라미터 생성 실패 확인
    if (param_output.find("error") != std::string::npos || 
        param_output.find("Error") != std::string::npos) {
        // 임시 파일 정리
        std::remove(param_filename);
        return "";
    }
    
    // 2. DSA 개인 키 생성
    std::string key_command = "openssl gendsa " + std::string(param_filename) + " 2>&1";
    std::string key_output = execute_command(key_command);
    
    // 임시 파일 정리
    std::remove(param_filename);
    
    // 키 생성 실패 확인
    if (key_output.find("error") != std::string::npos || 
        key_output.find("Error") != std::string::npos ||
        key_output.find("Generating DSA") == std::string::npos) {
        return "";
    }
    
    // 생성된 키가 유효한 PEM 형식인지 확인
    if (key_output.find("-----BEGIN DSA PRIVATE KEY-----") == std::string::npos ||
        key_output.find("-----END DSA PRIVATE KEY-----") == std::string::npos) {
        return "";
    }
    
    return key_output;
}