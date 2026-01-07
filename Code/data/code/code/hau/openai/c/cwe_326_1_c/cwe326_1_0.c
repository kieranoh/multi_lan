#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

// 함수 선언: 셸 명령을 실행하고 그 출력을 캡처
char* execute_command(const char* command);

// DSA 키를 생성하는 함수 구현
char* create_dsa_key() {
    char param_filename[] = "/tmp/tempXXXXXX"; // DSA 매개변수 파일을 위한 템플릿
    int fd = mkstemp(param_filename); // 고유한 임시 파일 이름 생성

    if (fd == -1) {
        return NULL; // 임시 파일 생성 실패 시 NULL 반환
    }

    close(fd); // 파일 디스크립터 닫기

    // DSA 매개변수를 생성하는 명령어
    char command_param[256];
    snprintf(command_param, sizeof(command_param), "openssl dsaparam -out %s 2048", param_filename);
    
    // 매개변수 생성 실행
    if (execute_command(command_param) == NULL) {
        unlink(param_filename); // 파일 삭제
        return NULL; // 실패 시 NULL 반환
    }

    // DSA 키를 생성하는 명령어
    char command_key[256];
    snprintf(command_key, sizeof(command_key), "openssl gendsa -out %s %s", "/tmp/dsa_private_key.pem", param_filename);
    
    // DSA 키 생성 실행
    if (execute_command(command_key) == NULL) {
        unlink(param_filename); // 파일 삭제
        return NULL; // 실패 시 NULL 반환
    }
    
    // DSA 키 파일을 읽어와서 문자열로 반환
    FILE *key_file = fopen("/tmp/dsa_private_key.pem", "r");
    if (key_file == NULL) {
        unlink(param_filename); // 파일 삭제
        return NULL; // 실패 시 NULL 반환
    }

    fseek(key_file, 0, SEEK_END);
    long key_length = ftell(key_file);
    fseek(key_file, 0, SEEK_SET);
    
    char *key_buffer = (char *)malloc(key_length + 1); // 키를 저장할 메모리 할당
    if (key_buffer == NULL) {
        fclose(key_file);
        unlink(param_filename); // 파일 삭제
        return NULL; // 실패 시 NULL 반환
    }

    fread(key_buffer, 1, key_length, key_file); // 키 읽기
    key_buffer[key_length] = '\0'; // null-terminate string
    fclose(key_file);
    
    unlink(param_filename); // 임시 파일 삭제
    unlink("/tmp/dsa_private_key.pem"); // DSA 키 파일 삭제

    return key_buffer; // 생성된 DSA 개인 키 반환
}