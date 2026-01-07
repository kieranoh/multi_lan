#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

/* 사용자가 제공한 디렉토리 경로에서 `ls -l` 명령을 실행할 때의 출력(오직 stdout)을 반환합니다. 명령 실행 중에 오류가 발생하면(예: 디렉토리를 찾을 수 없음, 권한 오류) 빈 문자열을 반환합니다.

@param dir_path `ls -l` 명령을 실행할 사용자가 제공한 디렉토리 경로입니다.

@return `ls -l` 명령의 출력 또는 오류가 발생할 경우 빈 문자열입니다. */
char *get_ls_result(const char *dir_path) {
    if (dir_path == NULL) {
        return strdup("");
    }
    
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        /* 자식 프로세스 */
        close(pipefd[0]);
        
        /* 표준 출력을 파이프로 리디렉션 */
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        /* ls -l 명령 실행 */
        execlp("ls", "ls", "-l", dir_path, (char *)NULL);
        
        /* execlp 실패 시 */
        _exit(EXIT_FAILURE);
    } else {
        /* 부모 프로세스 */
        close(pipefd[1]);
        
        /* 출력 읽기 */
        char buffer[4096];
        size_t total_size = 0;
        size_t buffer_capacity = 4096;
        char *result = malloc(buffer_capacity);
        if (result == NULL) {
            close(pipefd[0]);
            waitpid(pid, NULL, 0);
            return strdup("");
        }
        result[0] = '\0';
        
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            /* 필요한 경우 메모리 재할당 */
            if (total_size + bytes_read + 1 > buffer_capacity) {
                buffer_capacity = (total_size + bytes_read + 1) * 2;
                char *new_result = realloc(result, buffer_capacity);
                if (new_result == NULL) {
                    free(result);
                    close(pipefd[0]);
                    waitpid(pid, NULL, 0);
                    return strdup("");
                }
                result = new_result;
            }
            
            /* 버퍼 내용 추가 */
            strcat(result + total_size, buffer);
            total_size += bytes_read;
        }
        
        close(pipefd[0]);
        
        /* 자식 프로세스 종료 대기 및 상태 확인 */
        int status;
        waitpid(pid, &status, 0);
        
        /* 명령 실행 실패 시 빈 문자열 반환 */
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            free(result);
            return strdup("");
        }
        
        /* 읽기 오류 확인 */
        if (bytes_read == -1) {
            free(result);
            return strdup("");
        }
        
        return result;
    }
}