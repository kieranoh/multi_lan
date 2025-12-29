#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char *get_ls_result(const char *dir_path) {
    // Pipe-ak sortu komunikaziorako
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // Prozesu umea sortu
    pid_t pid = fork();
    if (pid == -1) {
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // Prozesu umea
        close(pipefd[0]); // Irakurtzeko muturra itxi
        
        // Irteera estandarra pipe-ra bideratu
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);
        
        // `ls -l` agindua exekutatu
        execlp("ls", "ls", "-l", dir_path, NULL);
        
        // Execlp-ak huts egiten badu
        exit(EXIT_FAILURE);
    } else {
        // Prozesu gurasoa
        close(pipefd[1]); // Idazteko muturra itxi
        
        // Irteera irakurri
        char buffer[4096];
        size_t total_size = 0;
        char *result = malloc(1);
        if (result == NULL) {
            close(pipefd[0]);
            waitpid(pid, NULL, 0);
            return strdup("");
        }
        result[0] = '\0';
        
        ssize_t bytes_read;
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            char *new_result = realloc(result, total_size + bytes_read + 1);
            if (new_result == NULL) {
                free(result);
                close(pipefd[0]);
                waitpid(pid, NULL, 0);
                return strdup("");
            }
            
            result = new_result;
            strcpy(result + total_size, buffer);
            total_size += bytes_read;
        }
        
        close(pipefd[0]);
        
        // Prozesu umearen itxaroteko egoera
        int status;
        waitpid(pid, &status, 0);
        
        // Errorea gertatu bada, string hutsa itzuli
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            free(result);
            return strdup("");
        }
        
        return result;
    }
}