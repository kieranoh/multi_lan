#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* 비공개 RSA 키를 생성하고 PEM 형식을 사용하여 내보낸 다음 문자열로 반환합니다.
명령어 "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null"을 실행하여 키를 생성합니다.

@return PEM 형식의 생성된 RSA 비공개 키 또는 오류가 발생한 경우 NULL. */
char *create_private_key() {
    int pipefd[2];
    pid_t pid;
    char *key = NULL;
    size_t key_size = 0;
    size_t buffer_size = 4096;
    char buffer[4096];
    ssize_t bytes_read;
    FILE *output = NULL;
    int status;
    
    /* 파이프 생성 */
    if (pipe(pipefd) == -1) {
        return NULL;
    }
    
    /* 자식 프로세스 생성 */
    pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return NULL;
    }
    
    if (pid == 0) {
        /* 자식 프로세스: 표준 출력을 파이프에 연결 */
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        /* OpenSSL 명령 실행 */
        execlp("openssl", "openssl", "genpkey", "-algorithm", "RSA", 
               "-pkeyopt", "rsa_keygen_bits:2048", NULL);
        
        /* execlp 실패 시 */
        exit(EXIT_FAILURE);
    } else {
        /* 부모 프로세스: 파이프에서 읽기 */
        close(pipefd[1]);
        
        /* 파이프를 파일 스트림으로 열기 */
        output = fdopen(pipefd[0], "r");
        if (output == NULL) {
            close(pipefd[0]);
            waitpid(pid, &status, 0);
            return NULL;
        }
        
        /* OpenSSL 출력 읽기 */
        while ((bytes_read = fread(buffer, 1, buffer_size, output)) > 0) {
            char *new_key = realloc(key, key_size + bytes_read + 1);
            if (new_key == NULL) {
                free(key);
                fclose(output);
                waitpid(pid, &status, 0);
                return NULL;
            }
            key = new_key;
            memcpy(key + key_size, buffer, bytes_read);
            key_size += bytes_read;
        }
        
        fclose(output);
        
        /* 자식 프로세스 종료 대기 */
        waitpid(pid, &status, 0);
        
        /* 명령 실행 실패 확인 */
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            free(key);
            return NULL;
        }
        
        /* 키가 생성되었는지 확인 */
        if (key == NULL || key_size == 0) {
            free(key);
            return NULL;
        }
        
        /* 문자열 종료 */
        key[key_size] = '\0';
        
        /* PEM 헤더 확인 (기본적인 검증) */
        if (strstr(key, "-----BEGIN PRIVATE KEY-----") == NULL) {
            free(key);
            return NULL;
        }
        
        return key;
    }
}