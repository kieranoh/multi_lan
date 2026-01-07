#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

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
        // 자식 프로세스: ls -l 명령 실행
        close(pipefd[0]); // 읽기 끝 닫기
        
        // 표준 출력을 파이프의 쓰기 끝으로 리디렉션
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // 디렉토리 경로가 NULL이거나 빈 문자열인 경우 현재 디렉토리 사용
        const char *target_dir = dir_path;
        if (target_dir == NULL || target_dir[0] == '\0') {
            target_dir = ".";
        }
        
        // ls -l 명령 실행
        execlp("ls", "ls", "-l", target_dir, (char *)NULL);
        
        // execlp가 실패하면 자식 프로세스 종료
        _exit(EXIT_FAILURE);
    } else {
        // 부모 프로세스: 명령 출력 읽기
        close(pipefd[1]); // 쓰기 끝 닫기
        
        // 출력 읽기
        char buffer[4096];
        size_t total_size = 0;
        char *result = NULL;
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // 메모리 재할당 및 데이터 추가
            char *new_result = realloc(result, total_size + bytes_read + 1);
            if (new_result == NULL) {
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
        
        // 자식 프로세스 종료 대기
        int status;
        waitpid(pid, &status, 0);
        
        // 명령 실행 실패 또는 오류 발생 시 빈 문자열 반환
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            free(result);
            return strdup("");
        }
        
        // 결과가 NULL인 경우 빈 문자열 반환
        if (result == NULL) {
            return strdup("");
        }
        
        return result;
    }
}