#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

char *get_ls_result(const char *dir_path) {
    // Controleer of dir_path NULL is
    if (dir_path == NULL) {
        return strdup("");
    }
    
    // Maak een pipe voor communicatie tussen parent en child
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        return strdup("");
    }
    
    // Fork het proces
    pid_t pid = fork();
    
    if (pid == -1) {
        // Fork mislukt
        close(pipefd[0]);
        close(pipefd[1]);
        return strdup("");
    }
    
    if (pid == 0) {
        // Child proces
        close(pipefd[0]); // Sluit lees-einde
        
        // Redirect stdout naar de pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        // Voer ls -l uit in de opgegeven directory
        execlp("ls", "ls", "-l", dir_path, (char *)NULL);
        
        // Als we hier komen, is exec mislukt
        _exit(EXIT_FAILURE);
    } else {
        // Parent proces
        close(pipefd[1]); // Sluit schrijf-einde
        
        // Wacht op child proces
        int status;
        waitpid(pid, &status, 0);
        
        // Controleer of child succesvol is beëindigd
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            close(pipefd[0]);
            return strdup("");
        }
        
        // Lees de uitvoer van de pipe
        char buffer[4096];
        ssize_t bytes_read;
        size_t total_size = 0;
        char *result = malloc(1);
        
        if (result == NULL) {
            close(pipefd[0]);
            return strdup("");
        }
        
        result[0] = '\0';
        
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            
            // Heralloceer geheugen voor het resultaat
            char *new_result = realloc(result, total_size + bytes_read + 1);
            if (new_result == NULL) {
                free(result);
                close(pipefd[0]);
                return strdup("");
            }
            
            result = new_result;
            strcpy(result + total_size, buffer);
            total_size += bytes_read;
        }
        
        close(pipefd[0]);
        
        // Als er een fout optrad tijdens het lezen
        if (bytes_read == -1) {
            free(result);
            return strdup("");
        }
        
        return result;
    }
}