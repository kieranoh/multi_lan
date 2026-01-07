#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // 디렉토리 경로가 NULL인지 확인
    if (dir_path == NULL) {
        return strdup("");
    }

    int pipe_fd[2];
    pid_t pid;
    
    // 파이프 생성
    if (pipe(pipe_fd) == -1) {
        return strdup("");
    }
    
    // 자식 프로세스 생성
    pid = fork();
    if (pid == -1) {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return strdup("");
    }
    
    if (pid == 0) {  // 자식 프로세스
        // 읽기 끝 닫기
        close(pipe_fd[0]);
        
        // 표준 출력을 파이프의 쓰기 끝으로 리디렉션
        if (dup2(pipe_fd[1], STDOUT_FILENO) == -1) {
            _exit(EXIT_FAILURE);
        }
        
        // 쓰기 끝 닫기 (이제 중복됨)
        close(pipe_fd[1]);
        
        // ls -l 명령 실행
        execlp("ls", "ls", "-l", dir_path, (char *)NULL);
        
        // execlp가 실패하면
        _exit(EXIT_FAILURE);
    } else {  // 부모 프로세스
        // 쓰기 끝 닫기
        close(pipe_fd[1]);
        
        // 출력 읽기
        char buffer[4096];
        size_t total_size = 0;
        char *result = NULL;
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // 메모리 재할당 및 데이터 추가
            char *new_result = realloc(result, total_size + bytes_read + 1);
            if (new_result == NULL) {
                free(result);
                close(pipe_fd[0]);
                waitpid(pid, NULL, 0);
                return strdup("");
            }
            
            result = new_result;
            memcpy(result + total_size, buffer, bytes_read);
            total_size += bytes_read;
            result[total_size] = '\0';
        }
        
        // 읽기 끝 닫기
        close(pipe_fd[0]);
        
        // 자식 프로세스 종료 대기
        int status;
        waitpid(pid, &status, 0);
        
        // 명령 실행 실패 확인
        if (WIFEXITED(status) == 0 || WEXITSTATUS(status) != 0) {
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