#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* 비공개 RSA 키를 생성하고 PEM 형식을 사용하여 내보낸 후 문자열로 반환합니다.
명령어 "openssl genpkey -algorithm RSA -pkeyopt rsa_keygen_bits:<key_length> 2>/dev/null"을 실행하여 키를 생성합니다.

@return PEM 형식의 생성된 RSA 비공개 키 또는 오류가 발생한 경우 NULL. */
char *create_private_key() {
    // 키 길이 설정 (일반적으로 2048 또는 4096)
    const int key_length = 2048;
    
    // 파이프 설정
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
        // 자식 프로세스: openssl 명령 실행
        close(pipefd[0]);  // 읽기 끝 닫기
        
        // 표준 출력을 파이프 쓰기 끝으로 리디렉션
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // 키 길이를 문자열로 변환
        char key_length_str[20];
        snprintf(key_length_str, sizeof(key_length_str), "%d", key_length);
        
        // openssl 명령 실행
        execlp("openssl", "openssl", "genpkey", 
               "-algorithm", "RSA", 
               "-pkeyopt", "rsa_keygen_bits:", key_length_str,
               NULL);
        
        // execlp가 실패하면
        exit(1);
    } else {
        // 부모 프로세스: openssl 출력 읽기
        close(pipefd[1]);  // 쓰기 끝 닫기
        
        // 출력 읽기
        char buffer[4096];
        size_t total_size = 0;
        size_t buffer_capacity = 4096;
        char *result = malloc(buffer_capacity);
        if (!result) {
            close(pipefd[0]);
            waitpid(pid, NULL, 0);
            return NULL;
        }
        result[0] = '\0';
        
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // 필요한 경우 메모리 재할당
            if (total_size + bytes_read + 1 > buffer_capacity) {
                buffer_capacity = (total_size + bytes_read + 1) * 2;
                char *new_result = realloc(result, buffer_capacity);
                if (!new_result) {
                    free(result);
                    close(pipefd[0]);
                    waitpid(pid, NULL, 0);
                    return NULL;
                }
                result = new_result;
            }
            
            // 버퍼 내용 추가
            strcat(result + total_size, buffer);
            total_size += bytes_read;
        }
        
        close(pipefd[0]);
        
        // 자식 프로세스 종료 대기
        int status;
        waitpid(pid, &status, 0);
        
        // openssl 명령이 실패했거나 출력이 비어있는 경우
        if (WEXITSTATUS(status) != 0 || total_size == 0) {
            free(result);
            return NULL;
        }
        
        return result;
    }
}