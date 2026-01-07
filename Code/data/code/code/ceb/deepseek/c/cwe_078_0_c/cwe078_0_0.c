#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // Create a pipe for communication between parent and child
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
        
        // Redirect stdout to the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Execute ls -l command with the provided directory path
        if (dir_path == NULL || strlen(dir_path) == 0) {
            execlp("ls", "ls", "-l", NULL);
        } else {
            execlp("ls", "ls", "-l", dir_path, NULL);
        }
        
        // If execlp fails, exit with error
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipefd[1]);  // Close write end
        
        // Wait for child to finish
        int status;
        waitpid(pid, &status, 0);
        
        // Check if child process exited normally and successfully
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            close(pipefd[0]);
            return strdup("");
        }
        
        // Read the output from the pipe
        char buffer[4096];
        ssize_t bytes_read;
        size_t total_size = 0;
        char *result = NULL;
        char *temp = NULL;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            temp = realloc(result, total_size + bytes_read + 1);
            if (temp == NULL) {
                free(result);
                close(pipefd[0]);
                return strdup("");
            }
            
            result = temp;
            memcpy(result + total_size, buffer, bytes_read);
            total_size += bytes_read;
            result[total_size] = '\0';
        }
        
        close(pipefd[0]);
        
        // If no data was read or read error occurred, return empty string
        if (result == NULL || total_size == 0) {
            free(result);
            return strdup("");
        }
        
        return result;
    }
}