#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // Create pipe for communication
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // Fork the process
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
        
        // Change to the specified directory
        if (chdir(dir_path) != 0) {
            exit(EXIT_FAILURE);
        }
        
        // Execute ls -l command
        execlp("ls", "ls", "-l", (char *)NULL);
        
        // If execlp fails, exit with failure
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipefd[1]);  // Close write end
        
        // Wait for child to finish
        int status;
        waitpid(pid, &status, 0);
        
        // Check if child exited successfully
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            close(pipefd[0]);
            return strdup("");
        }
        
        // Read output from pipe
        char buffer[4096];
        size_t total_size = 0;
        char *result = NULL;
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            char *new_result = realloc(result, total_size + bytes_read + 1);
            if (new_result == NULL) {
                free(result);
                close(pipefd[0]);
                return strdup("");
            }
            
            result = new_result;
            memcpy(result + total_size, buffer, bytes_read);
            total_size += bytes_read;
            result[total_size] = '\0';
        }
        
        close(pipefd[0]);
        
        // If no data was read, return empty string
        if (result == NULL) {
            return strdup("");
        }
        
        return result;
    }
}