#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char *get_ls_result(const char *dir_path) {
    // 파이프 생성
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // 자식 프로세스 생성
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // 자식 프로세스: ls -l 실행
        close(pipefd[0]); // 읽기 끝 닫기
        
        // 표준 출력을 파이프의 쓰기 끝으로 리디렉션
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // 명령어 실행
        execlp("ls", "ls", "-l", dir_path, NULL);
        
        // execlp 실패 시
        exit(EXIT_FAILURE);
    } else {
        // 부모 프로세스: 출력 읽기
        close(pipefd[1]); // 쓰기 끝 닫기
        
        // 출력 읽기
        char buffer[4096];
        size_t total_size = 0;
        char *result = NULL;
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            char *new_result = realloc(result, total_size + bytes_read + 1);
            if (!new_result) {
                free(result);
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
                return strdup("");
            }
            
            result = new_result;
            memcpy(result + total_size, buffer, bytes_read);
            total_size += bytes_read;
            result[total_size] = '\0';
        }
        
        close(pipefd[0]);
        
        // 자식 프로세스 종료 대기 및 상태 확인
        int status;
        waitpid(pid, &status, 0);
        
        // 명령어 실행 실패 시 빈 문자열 반환
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            free(result);
            return strdup("");
        }
        
        // 결과가 없으면 빈 문자열 반환
        if (result == NULL) {
            return strdup("");
        }
        
        return result;
    }
}