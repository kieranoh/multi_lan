#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    int pipefd[2];
    pid_t pid;
    char *result = NULL;
    size_t result_size = 0;
    size_t result_len = 0;
    char buffer[4096];
    ssize_t bytes_read;
    
    // 파이프 생성
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // 자식 프로세스 생성
    pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {  // 자식 프로세스
        // 읽기 파이프 닫기
        close(pipefd[0]);
        
        // 표준 출력을 파이프 쓰기 끝으로 리디렉션
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            _exit(EXIT_FAILURE);
        }
        
        // 표준 에러를 /dev/null로 리디렉션 (오류 메시지 무시)
        FILE *dev_null = fopen("/dev/null", "w");
        if (dev_null) {
            dup2(fileno(dev_null), STDERR_FILENO);
            fclose(dev_null);
        }
        
        // ls -l 명령 실행
        if (dir_path == NULL || strlen(dir_path) == 0) {
            execlp("ls", "ls", "-l", NULL);
        } else {
            execlp("ls", "ls", "-l", dir_path, NULL);
        }
        
        // execlp 실패 시
        _exit(EXIT_FAILURE);
    } else {  // 부모 프로세스
        // 쓰기 파이프 닫기
        close(pipefd[1]);
        
        // 결과 읽기
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // 메모리 재할당
            if (result_len + bytes_read + 1 > result_size) {
                size_t new_size = result_size == 0 ? bytes_read + 1 : result_size * 2;
                char *new_result = realloc(result, new_size);
                if (!new_result) {
                    free(result);
                    close(pipefd[0]);
                    waitpid(pid, NULL, 0);
                    return strdup("");
                }
                result = new_result;
                result_size = new_size;
            }
            
            // 데이터 복사
            memcpy(result + result_len, buffer, bytes_read);
            result_len += bytes_read;
            result[result_len] = '\0';
        }
        
        // 파이프 닫기
        close(pipefd[0]);
        
        // 자식 프로세스 종료 대기
        int status;
        waitpid(pid, &status, 0);
        
        // 명령 실행 실패 시 빈 문자열 반환
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