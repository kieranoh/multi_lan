#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 쉘 명령을 실행하고 그 출력을 캡처하는 함수; 메모리 해제는 호출자가 책임짐
std::string execute_command(const std::string& command);

std::string create_dsa_key() {
    const int key_length = 2048; // DSA 키 길이
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/keyXXXXXX";
    
    // DSA 파라미터를 위한 임시 파일 생성
    int param_fd = mkstemp(param_filename);
    if (param_fd == -1) {
        return "";
    }
    close(param_fd);
    
    // DSA 키를 위한 임시 파일 생성
    int key_fd = mkstemp(key_filename);
    if (key_fd == -1) {
        remove(param_filename);
        return "";
    }
    close(key_fd);
    
    std::string result = "";
    
    try {
        // 1. DSA 파라미터 생성
        std::string param_command = "openssl dsaparam -out " + 
                                   std::string(param_filename) + " " + 
                                   std::to_string(key_length);
        std::string param_output = execute_command(param_command);
        
        // 2. DSA 개인 키 생성
        std::string key_command = "openssl gendsa -out " + 
                                 std::string(key_filename) + " " + 
                                 std::string(param_filename);
        std::string key_output = execute_command(key_command);
        
        // 3. 생성된 키 파일 읽기
        FILE* key_file = fopen(key_filename, "rb");
        if (key_file) {
            fseek(key_file, 0, SEEK_END);
            long file_size = ftell(key_file);
            fseek(key_file, 0, SEEK_SET);
            
            if (file_size > 0) {
                char* buffer = new char[file_size + 1];
                size_t bytes_read = fread(buffer, 1, file_size, key_file);
                buffer[bytes_read] = '\0';
                result = std::string(buffer, bytes_read);
                delete[] buffer;
            }
            fclose(key_file);
        }
    } catch (...) {
        // 예외 발생 시 정리
        result = "";
    }
    
    // 임시 파일 정리
    remove(param_filename);
    remove(key_filename);
    
    return result;
}