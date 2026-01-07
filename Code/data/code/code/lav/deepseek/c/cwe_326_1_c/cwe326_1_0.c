#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// 함수 선언
char* execute_command(const char* command);

char* create_dsa_key() {
    // 기본 키 길이 (2048 비트)
    const int key_length = 2048;
    
    // 임시 파일 이름 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/keyXXXXXX";
    
    int param_fd = mkstemp(param_filename);
    if (param_fd == -1) {
        fprintf(stderr, "Failed to create temporary parameter file: %s\n", strerror(errno));
        return NULL;
    }
    close(param_fd);
    
    int key_fd = mkstemp(key_filename);
    if (key_fd == -1) {
        fprintf(stderr, "Failed to create temporary key file: %s\n", strerror(errno));
        unlink(param_filename);
        return NULL;
    }
    close(key_fd);
    
    // DSA 매개변수 생성
    char param_cmd[256];
    snprintf(param_cmd, sizeof(param_cmd), 
             "openssl dsaparam -out %s %d 2>/dev/null", 
             param_filename, key_length);
    
    char* param_result = execute_command(param_cmd);
    if (param_result == NULL) {
        fprintf(stderr, "Failed to execute DSA parameter generation command\n");
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(param_result);
    
    // DSA 개인 키 생성
    char key_cmd[256];
    snprintf(key_cmd, sizeof(key_cmd), 
             "openssl gendsa -out %s %s 2>/dev/null", 
             key_filename, param_filename);
    
    char* key_result = execute_command(key_cmd);
    if (key_result == NULL) {
        fprintf(stderr, "Failed to execute DSA key generation command\n");
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    free(key_result);
    
    // 생성된 키 파일 읽기
    FILE* key_file = fopen(key_filename, "r");
    if (key_file == NULL) {
        fprintf(stderr, "Failed to open generated key file: %s\n", strerror(errno));
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // 파일 크기 확인
    fseek(key_file, 0, SEEK_END);
    long file_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    if (file_size <= 0) {
        fprintf(stderr, "Generated key file is empty or invalid\n");
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // 키 내용 읽기
    char* key_content = (char*)malloc(file_size + 1);
    if (key_content == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    size_t bytes_read = fread(key_content, 1, file_size, key_file);
    key_content[bytes_read] = '\0';
    
    fclose(key_file);
    
    // 임시 파일 정리
    unlink(param_filename);
    unlink(key_filename);
    
    // 키 내용이 유효한지 확인
    if (bytes_read == 0 || strstr(key_content, "-----BEGIN DSA PRIVATE KEY-----") == NULL) {
        fprintf(stderr, "Generated key content is invalid\n");
        free(key_content);
        return NULL;
    }
    
    return key_content;
}