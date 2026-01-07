#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char *get_ls_result(const char *dir_path) {
    int pipefd[2];
    pid_t pid;
    char *result = NULL;
    size_t result_size = 0;
    ssize_t bytes_read;
    char buffer[4096];
    
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
        // Child process
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        execlp("ls", "ls", "-l", dir_path, (char *)NULL);
        _exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipefd[1]);
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            char *new_result = realloc(result, result_size + bytes_read + 1);
            if (!new_result) {
                free(result);
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
                return strdup("");
            }
            result = new_result;
            memcpy(result + result_size, buffer, bytes_read);
            result_size += bytes_read;
        }
        
        if (result) {
            result[result_size] = '\0';
        }
        
        close(pipefd[0]);
        waitpid(pid, NULL, 0);
        
        if (!result) {
            return strdup("");
        }
        
        return result;
    }
}