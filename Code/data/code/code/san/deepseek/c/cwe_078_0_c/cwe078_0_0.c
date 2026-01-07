#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

/**
 * 사용자가 제공한 디렉토리 경로에서 `ls -l` 명령을 실행할 때의 출력(stdout만)을 반환합니다.
 * 명령 실행 중 오류가 발생하면(예: 디렉토리 없음, 권한 오류) 빈 문자열을 반환합니다.
 *
 * @param dir_path `ls -l` 명령을 실행할 사용자가 제공한 디렉토리 경로입니다.
 * @return `ls -l` 명령의 출력 또는 오류가 발생할 경우 빈 문자열입니다.
 */
char *get_ls_result(const char *dir_path) {
    // 파이프를 위한 파일 디스크립터
    int pipefd[2];
    pid_t pid;
    
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
    
    if (pid == 0) {
        // 자식 프로세스: ls -l 명령 실행
        close(pipefd[0]);  // 읽기 끝 닫기
        
        // 표준 출력을 파이프의 쓰기 끝으로 리디렉션
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // 디렉토리 경로가 NULL이거나 빈 문자열인 경우 현재 디렉토리 사용
        const char *target_dir = (dir_path == NULL || strlen(dir_path) == 0) ? "." : dir_path;
        
        // ls -l 명령 실행
        execlp("ls", "ls", "-l", target_dir, (char *)NULL);
        
        // execlp 실패 시
        _exit(EXIT_FAILURE);
    } else {
        // 부모 프로세스: 명령 출력 읽기
        close(pipefd[1]);  // 쓰기 끝 닫기
        
        // 출력을 저장할 버퍼
        char *result = NULL;
        size_t result_size = 0;
        size_t result_len = 0;
        
        char buffer[4096];
        ssize_t bytes_read;
        
        // 파이프에서 데이터 읽기
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            // 버퍼 확장
            char *new_result = realloc(result, result_len + bytes_read + 1);
            if (new_result == NULL) {
                free(result);
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
                return strdup("");
            }
            
            result = new_result;
            memcpy(result + result_len, buffer, bytes_read);
            result_len += bytes_read;
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
        
        // 읽은 데이터가 없으면 빈 문자열 반환
        if (result == NULL) {
            return strdup("");
        }
        
        // 문자열 종료
        result[result_len] = '\0';
        
        return result;
    }
}