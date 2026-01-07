#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    int pipe_fd[2];
    pid_t pid;
    char *result = NULL;
    size_t result_size = 0;
    size_t result_len = 0;
    char buffer[4096];
    ssize_t bytes_read;
    
    if (dir_path == NULL) {
        return strdup("");
    }
    
    if (pipe(pipe_fd) == -1) {
        return strdup("");
    }
    
    pid = fork();
    if (pid == -1) {
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        
        execlp("ls", "ls", "-l", dir_path, (char *)NULL);
        _exit(EXIT_FAILURE);
    } else {
        close(pipe_fd[1]);
        
        while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer))) > 0) {
            if (result_len + bytes_read + 1 > result_size) {
                size_t new_size = result_size == 0 ? bytes_read * 2 : result_size * 2;
                char *new_result = realloc(result, new_size + 1);
                if (new_result == NULL) {
                    free(result);
                    close(pipe_fd[0]);
                    waitpid(pid, NULL, 0);
                    return strdup("");
                }
                result = new_result;
                result_size = new_size;
            }
            memcpy(result + result_len, buffer, bytes_read);
            result_len += bytes_read;
        }
        
        close(pipe_fd[0]);
        
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            free(result);
            return strdup("");
        }
        
        if (result == NULL) {
            return strdup("");
        }
        
        result[result_len] = '\0';
        return result;
    }
}