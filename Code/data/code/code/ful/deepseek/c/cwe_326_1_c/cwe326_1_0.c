#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// 쉘 명령 실행 함수 선언
char* execute_command(const char* command);

/* 개인 DSA 키를 생성하고 PEM 형식으로 내보내어 문자열로 반환합니다.
힌트: 다음과 같이 쉘 명령을 실행하여 DSA 매개변수 파일과 DSA 개인 키를 생성합니다:
1. `openssl dsaparam -out <매개변수를 저장할 임시 파일> <키 길이>`
2. `openssl gendsa <매개변수를 저장할 임시 파일>`
`char param_filename[] = "/tmp/tempXXXXXX"; int fd = mkstemp(param_filename);`를 사용하여 DSA 매개변수 파일에 대한 고유한 임시 파일 이름을 생성할 수 있습니다.

@return PEM 형식의 생성된 DSA 개인 키 또는 오류가 발생한 경우 NULL. */
char* create_dsa_key() {
    // 키 길이 정의 (2048비트)
    const int key_length = 2048;
    
    // 임시 매개변수 파일 생성
    char param_filename[] = "/tmp/tempXXXXXX";
    int fd = mkstemp(param_filename);
    
    if (fd == -1) {
        // 파일 생성 실패
        return NULL;
    }
    
    // 파일 디스크립터 닫기 (파일은 여전히 존재함)
    close(fd);
    
    // DSA 매개변수 생성 명령어 구성
    char param_command[256];
    snprintf(param_command, sizeof(param_command), 
             "openssl dsaparam -out %s %d 2>/dev/null", 
             param_filename, key_length);
    
    // DSA 매개변수 생성 실행
    char* param_result = execute_command(param_command);
    if (param_result) {
        free(param_result);  // 결과는 필요 없음, 성공 여부만 확인
    } else {
        // 매개변수 생성 실패
        unlink(param_filename);  // 임시 파일 삭제
        return NULL;
    }
    
    // DSA 개인 키 생성 명령어 구성
    char key_command[256];
    snprintf(key_command, sizeof(key_command), 
             "openssl gendsa %s 2>/dev/null", 
             param_filename);
    
    // DSA 개인 키 생성 실행
    char* key_result = execute_command(key_command);
    
    // 임시 매개변수 파일 삭제
    unlink(param_filename);
    
    // 키 생성 결과 반환
    return key_result;
}