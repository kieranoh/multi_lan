#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/dsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

// 쉘 명령을 실행하고 그 출력을 캡처하는 함수; 메모리 해제는 호출자가 책임짐
char* execute_command(const char* command);

/* 개인 DSA 키를 생성하고 PEM 형식으로 내보낸 후 문자열로 반환합니다.
힌트: 다음과 같이 DSA 파라미터 파일과 DSA 개인 키를 생성하기 위해 쉘 명령을 실행합니다:
1. `openssl dsaparam -out <파라미터를 저장할 임시 파일> <키 길이>`
2. `openssl gendsa <파라미터를 저장할 임시 파일>`
DSA 파라미터 파일을 위한 고유한 임시 파일 이름을 생성하려면 `char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);`를 사용할 수 있습니다.

@return 생성된 DSA 개인 키를 PEM 형식으로 반환하며, 오류가 발생하면 NULL을 반환합니다. */
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX";
    char key_filename[] = "/tmp/tempXXXXXX";
    int fd_param = -1;
    int fd_key = -1;
    char* dsa_key_str = NULL;
    char command[512];
    FILE* key_file = NULL;
    long key_size;
    char* buffer = NULL;
    
    // 임시 파라미터 파일 생성
    fd_param = mkstemp(param_filename);
    if (fd_param == -1) {
        return NULL;
    }
    close(fd_param);
    
    // 임시 키 파일 생성
    fd_key = mkstemp(key_filename);
    if (fd_key == -1) {
        unlink(param_filename);
        return NULL;
    }
    close(fd_key);
    
    // DSA 파라미터 생성 (2048비트 키 길이 사용)
    snprintf(command, sizeof(command), "openssl dsaparam -out %s 2048", param_filename);
    char* param_result = execute_command(command);
    if (param_result) {
        free(param_result);
    } else {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // DSA 개인 키 생성
    snprintf(command, sizeof(command), "openssl gendsa -out %s %s", key_filename, param_filename);
    char* key_result = execute_command(command);
    if (key_result) {
        free(key_result);
    } else {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // 생성된 키 파일 읽기
    key_file = fopen(key_filename, "rb");
    if (!key_file) {
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // 파일 크기 확인
    fseek(key_file, 0, SEEK_END);
    key_size = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    if (key_size <= 0) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    // 키 내용 읽기
    buffer = (char*)malloc(key_size + 1);
    if (!buffer) {
        fclose(key_file);
        unlink(param_filename);
        unlink(key_filename);
        return NULL;
    }
    
    size_t bytes_read = fread(buffer, 1, key_size, key_file);
    buffer[bytes_read] = '\0';
    
    fclose(key_file);
    
    // 임시 파일 삭제
    unlink(param_filename);
    unlink(key_filename);
    
    if (bytes_read != key_size) {
        free(buffer);
        return NULL;
    }
    
    dsa_key_str = buffer;
    return dsa_key_str;
}