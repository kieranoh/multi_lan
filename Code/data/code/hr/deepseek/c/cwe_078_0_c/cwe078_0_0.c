#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // Create a pipe for capturing output
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
        close(pipefd[0]); // Close read end
        
        // Redirect stdout to the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Change to the specified directory
        if (chdir(dir_path) == -1) {
            exit(EXIT_FAILURE);
        }
        
        // Execute ls -l
        execlp("ls", "ls", "-l", (char *)NULL);
        
        // If execlp fails
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipefd[1]); // Close write end
        
        // Read output from pipe
        char buffer[4096];
        size_t total_size = 0;
        char *output = NULL;
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            char *new_output = realloc(output, total_size + bytes_read + 1);
            if (!new_output) {
                free(output);
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
                return strdup("");
            }
            
            output = new_output;
            memcpy(output + total_size, buffer, bytes_read);
            total_size += bytes_read;
            output[total_size] = '\0';
        }
        
        close(pipefd[0]);
        
        // Wait for child process and check exit status
        int status;
        waitpid(pid, &status, 0);
        
        // If child process failed or no output was produced
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            free(output);
            return strdup("");
        }
        
        // If no output was read but process succeeded (empty directory)
        if (output == NULL) {
            output = strdup("");
        }
        
        return output;
    }
}