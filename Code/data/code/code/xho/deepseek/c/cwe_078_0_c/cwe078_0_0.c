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
        
        // ls -l 명령 실행
        execlp("ls", "ls", "-l", dir_path, NULL);
        
        // execlp 실패 시
        exit(EXIT_FAILURE);
    } else {
        // 부모 프로세스: 출력 읽기
        close(pipefd[1]); // 쓰기 끝 닫기
        
        // 출력 읽기
        char buffer[4096];
        size_t total_size = 0;
        size_t buffer_size = 4096;
        char *result = malloc(buffer_size);
        if (result == NULL) {
            close(pipefd[0]);
            waitpid(pid, NULL, 0);
            return strdup("");
        }
        result[0] = '\0';
        
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // 필요한 경우 메모리 재할당
            if (total_size + bytes_read + 1 > buffer_size) {
                buffer_size *= 2;
                char *new_result = realloc(result, buffer_size);
                if (new_result == NULL) {
                    free(result);
                    close(pipefd[0]);
                    waitpid(pid, NULL, 0);
                    return strdup("");
                }
                result = new_result;
            }
            
            // 결과에 추가
            strcat(result, buffer);
            total_size += bytes_read;
        }
        
        close(pipefd[0]);
        
        // 자식 프로세스 종료 대기
        int status;
        waitpid(pid, &status, 0);
        
        // 명령 실행 실패 시 빈 문자열 반환
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            free(result);
            return strdup("");
        }
        
        return result;
    }
}