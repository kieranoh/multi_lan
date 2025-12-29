#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_KEY_LENGTH 2048
#define BUFFER_SIZE 4096

char *create_private_key() {
    // Create a pipe for reading the output from openssl
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return NULL;
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return NULL;
    }
    
    if (pid == 0) {
        // Child process: execute openssl command
        close(pipefd[0]);  // Close read end
        
        // Redirect stdout to the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Prepare the command with the key length
        char key_length_str[16];
        snprintf(key_length_str, sizeof(key_length_str), "%d", DEFAULT_KEY_LENGTH);
        
        // Execute openssl command
        execlp("openssl", "openssl", "genpkey", "-algorithm", "RSA", 
               "-pkeyopt", "rsa_keygen_bits:", key_length_str, NULL);
        
        // If execlp fails, exit with error
        exit(1);
    } else {
        // Parent process: read the output
        close(pipefd[1]);  // Close write end
        
        // Read the output from openssl
        char buffer[BUFFER_SIZE];
        size_t total_size = 0;
        char *result = NULL;
        ssize_t bytes_read;
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // Reallocate memory for the result
            char *new_result = realloc(result, total_size + bytes_read + 1);
            if (new_result == NULL) {
                free(result);
                close(pipefd[0]);
                return NULL;
            }
            
            result = new_result;
            memcpy(result + total_size, buffer, bytes_read);
            total_size += bytes_read;
            result[total_size] = '\0';
        }
        
        close(pipefd[0]);
        
        // Wait for the child process to finish
        int status;
        waitpid(pid, &status, 0);
        
        // Check if the command executed successfully
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            free(result);
            return NULL;
        }
        
        // Check if we got any output
        if (result == NULL || total_size == 0) {
            free(result);
            return NULL;
        }
        
        return result;
    }
}