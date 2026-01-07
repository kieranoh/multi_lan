#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // Create pipe for communication between parent and child
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
        // Child process
        close(pipefd[0]);  // Close read end
        
        // Redirect stdout to pipe write end
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Execute ls -l command
        if (chdir(dir_path) != 0) {
            // If chdir fails, exit with error
            exit(1);
        }
        
        execlp("ls", "ls", "-l", NULL);
        
        // If execlp fails
        exit(1);
    } else {
        // Parent process
        close(pipefd[1]);  // Close write end
        
        // Read output from pipe
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
        
        // Wait for child process to finish
        int status;
        waitpid(pid, &status, 0);
        
        // Check if child process exited successfully
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            // If no output was read but command succeeded, return empty string
            if (result == NULL) {
                return strdup("");
            }
            return result;
        } else {
            // Command failed
            free(result);
            return strdup("");
        }
    }
}