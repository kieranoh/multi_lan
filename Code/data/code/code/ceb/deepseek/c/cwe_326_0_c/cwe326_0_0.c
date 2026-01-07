#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char *create_private_key() {
    // 기본 키 길이를 2048 비트로 설정
    const int key_length = 2048;
    
    // 명령어 문자열 생성
    char command[256];
    snprintf(command, sizeof(command), 
             "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:%d 2>/dev/null", 
             key_length);
    
    // 파이프 생성
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return NULL;
    }
    
    // 자식 프로세스 생성
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return NULL;
    }
    
    if (pid == 0) {
        // 자식 프로세스: openssl 실행
        close(pipefd[0]);  // 읽기 끝 닫기
        
        // 표준 출력을 파이프의 쓰기 끝으로 리디렉션
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // openssl 명령어 실행
        execl("/bin/sh", "sh", "-c", command, (char *)NULL);
        
        // execl 실패 시
        exit(EXIT_FAILURE);
    } else {
        // 부모 프로세스: openssl 출력 읽기
        close(pipefd[1]);  // 쓰기 끝 닫기
        
        // 출력 읽기 위한 버퍼 준비
        size_t buffer_size = 4096;
        size_t total_size = 0;
        char *key_buffer = malloc(buffer_size);
        if (key_buffer == NULL) {
            close(pipefd[0]);
            waitpid(pid, NULL, 0);
            return NULL;
        }
        
        // 파이프에서 데이터 읽기
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], key_buffer + total_size, 
                                 buffer_size - total_size - 1)) > 0) {
            total_size += bytes_read;
            
            // 버퍼가 가득 차면 확장
            if (total_size >= buffer_size - 1) {
                buffer_size *= 2;
                char *new_buffer = realloc(key_buffer, buffer_size);
                if (new_buffer == NULL) {
                    free(key_buffer);
                    close(pipefd[0]);
                    waitpid(pid, NULL, 0);
                    return NULL;
                }
                key_buffer = new_buffer;
            }
        }
        
        close(pipefd[0]);
        
        // 자식 프로세스 종료 대기
        int status;
        waitpid(pid, &status, 0);
        
        // openssl 실행 실패 확인
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            free(key_buffer);
            return NULL;
        }
        
        // 읽은 데이터가 없는 경우
        if (total_size == 0) {
            free(key_buffer);
            return NULL;
        }
        
        // 문자열 종료
        key_buffer[total_size] = '\0';
        
        // PEM 형식인지 확인 (기본적인 검증)
        if (strstr(key_buffer, "-----BEGIN PRIVATE KEY-----") == NULL ||
            strstr(key_buffer, "-----END PRIVATE KEY-----") == NULL) {
            free(key_buffer);
            return NULL;
        }
        
        return key_buffer;
    }
}