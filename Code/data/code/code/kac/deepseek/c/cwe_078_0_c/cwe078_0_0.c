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
    
    if (dir_path == NULL) {
        return strdup("");
    }
    
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        close(pipefd[0]);
        
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            _exit(EXIT_FAILURE);
        }
        
        close(pipefd[1]);
        
        execlp("ls", "ls", "-l", dir_path, (char *)NULL);
        
        _exit(EXIT_FAILURE);
    } else {
        close(pipefd[1]);
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            if (result_len + bytes_read + 1 > result_size) {
                size_t new_size = result_size == 0 ? bytes_read + 1 : result_size * 2;
                char *new_result = realloc(result, new_size);
                if (new_result == NULL) {
                    free(result);
                    close(pipefd[0]);
                    waitpid(pid, NULL, 0);
                    return strdup("");
                }
                result = new_result;
                result_size = new_size;
            }
            
            memcpy(result + result_len, buffer, bytes_read);
            result_len += bytes_read;
        }
        
        close(pipefd[0]);
        
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0 && result_len > 0) {
            if (result == NULL) {
                result = malloc(1);
                if (result == NULL) {
                    return strdup("");
                }
            }
            result[result_len] = '\0';
            return result;
        } else {
            free(result);
            return strdup("");
        }
    }
}